#include "graphics.h"

static char *video_mem;
static vbe_mode_info_t vmi;
static uint8_t bytes_per_pixel;
static uint32_t vram_size;

int vg_set_mode(uint16_t mode) {
    reg86_t reg;
    bzero(&reg, sizeof(reg86_t));

    reg.intno = VBE_INT_NO;
    reg.ah = VBE_AH;
    reg.al = VBE_SET_VIDEO_MODE;
    reg.bx = mode | BIT(14);

    return sys_int86(&reg);
}

int vg_init_graphics(uint16_t mode) {
    if (vbe_get_mode_info(mode,&vmi) != OK) { return !OK; }

    struct minix_mem_range mr;
    unsigned int vram_base = vmi.PhysBasePtr;  
    vram_size = vmi.BytesPerScanLine * vmi.YResolution;  
    bytes_per_pixel = vmi.BytesPerScanLine / vmi.XResolution;
    printf("Bytes per pixel: %d\n", bytes_per_pixel);
    int r;				    

    mr.mr_base = (phys_bytes) vram_base;	
    mr.mr_limit = mr.mr_base + vram_size;  

    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) {
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    }

    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

    if(video_mem == MAP_FAILED)
    panic("couldn't map video memory");

    if (vg_set_mode(mode) != OK) { return !OK; }

    return OK;
}

int vg_draw_pixel(uint16_t x, uint16_t y, uint32_t color) {
    if (x < 0 || y < 0 || x >= vmi.XResolution || y >= vmi.YResolution) { return !OK; }
    uint32_t pos = bytes_per_pixel * (x + y * vmi.XResolution);
    color = color & set_bits(vmi.BitsPerPixel);
    memcpy(video_mem + pos, &color, bytes_per_pixel);
    return OK;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (int i = 0; i < len; i++) {
        vg_draw_pixel(x + i, y, color);
    }
    return OK;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    for (int i = 0; i < height; i++) {
        vg_draw_hline(x, y + i, width, color);
    }
    return OK;
}

int (vg_draw_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
    uint32_t width = vmi.XResolution / no_rectangles;
    uint32_t height = vmi.YResolution / no_rectangles;
    if (mode == 0x105) {
        for (int i = 0; i < no_rectangles; i++) {
            for (int j = 0; j < no_rectangles; j++) {
                uint32_t color = (first + (i * no_rectangles + j) * step) % (1 << vmi.BitsPerPixel);
                vg_draw_rectangle(j * width, i * height, width, height, color);
            }
        }
    } else {
        uint32_t first_red = (first >> vmi.RedFieldPosition) & set_bits(vmi.RedMaskSize);
        uint32_t first_green = (first >> vmi.GreenFieldPosition) & set_bits(vmi.GreenMaskSize);
        uint32_t first_blue = (first >> vmi.BlueFieldPosition) & set_bits(vmi.BlueMaskSize);

        for (int i = 0; i < no_rectangles; i++) {
            for (int j = 0; j < no_rectangles; j++) {
                uint32_t red = (first_red + j * step) % (1 << vmi.RedMaskSize);
                uint32_t green = (first_green + i * step) % (1 << vmi.GreenMaskSize);
                uint32_t blue = (first_blue + (j + i) * step) % (1 << vmi.BlueMaskSize);

                uint32_t color = (red << vmi.RedFieldPosition) | 
                    (green << vmi.GreenFieldPosition) |
                    (blue << vmi.BlueFieldPosition);

                vg_draw_rectangle(j * width, i * height, width, height, color);
            }
        }
    }
    return OK;
}

int (vg_draw_sprite)(unsigned char* sprite, xpm_image_t img, uint16_t x, uint16_t y) {
    for (int i = 0; i < img.height; i++) {
        uint32_t pos = bytes_per_pixel * (x + (y + i) * vmi.XResolution);
        uint32_t pos_sprite = bytes_per_pixel * i * img.width;
        memcpy(video_mem + pos, sprite + pos_sprite, bytes_per_pixel * img.width);
    }
    return OK;
}

uint32_t set_bits(uint32_t n) {
    uint32_t res = 0x0;
    for (uint32_t i = 0; i < n; i++) {
        res |= BIT(i);
    }
    return res;
}
