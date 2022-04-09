#include <graphics.h>

static char * video_mem;
static vbe_mode_info_t vmi;

int (set_video_mode)(uint16_t mode) {
  reg86_t reg86;

  memset(&reg86, 0, sizeof(reg86));

  reg86.intno = VBE_INTERRUPT_VECTOR;
  reg86.ah = VBE_AH;
  reg86.al = SET_VBE_MODE;
  reg86.bx = mode | LINEAR_FRAME_BUFFER;

  if (sys_int86(&reg86) != OK) {
    printf("vg_init(): sys_int86() failed\n");
    return !OK;
  }
  
  return OK;
}

void * (vg_init)(uint16_t mode) {
  int r;	

  memset(&vmi, 0, sizeof(vmi));

  if (vbe_get_mode_info(mode, &vmi) != OK) {
    printf("vg_init(): vbe_get_mode_info() failed\n");
    return NULL;
  }

  struct minix_mem_range mr;
  unsigned int vram_base = vmi.PhysBasePtr;
  unsigned int vram_size = vmi.XResolution * vmi.YResolution * vmi.BitsPerPixel;

  /* Allow memory mapping */

  mr.mr_base = (phys_bytes) vram_base;	
  mr.mr_limit = mr.mr_base + vram_size;  

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */

  video_mem = (char *) vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED)
    panic("couldn't map video memory");

  set_video_mode(mode);

  return NULL;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {

  int bytes_per_pixel = vmi.BytesPerScanLine / vmi.XResolution;

  color &= set_bits(0,vmi.BitsPerPixel);

  memcpy(video_mem + bytes_per_pixel * (x + y * vmi.XResolution), &color, bytes_per_pixel);

  return OK;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = 0; i < len; i++) {
    if (vg_draw_pixel(x+i,y,color) != OK) { return !OK; }
  }
  return OK;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (int i = 0; i < height; i++) {
    if (vg_draw_hline(x,y+i,width,color) != OK) { return !OK; }
  }
  return OK;
}

int (vg_draw_matrix)(bool indexed_mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  uint16_t width = vmi.XResolution / no_rectangles;
  uint16_t height = vmi.YResolution / no_rectangles;
  uint32_t color;
  uint8_t red, red_first, green, green_first, blue, blue_first;

  if (!indexed_mode) {
    red_first = (first >> vmi.RedFieldPosition) & set_bits(0, vmi.RedMaskSize);
    green_first = (first >> vmi.GreenFieldPosition) & set_bits(0, vmi.GreenMaskSize);
    blue_first = (first >> vmi.BlueFieldPosition) & set_bits(0, vmi.BlueMaskSize);
  }

  for (int row = 0; row < no_rectangles; row++) {
    for (int col = 0; col < no_rectangles; col++) {
      if (indexed_mode) {
        color = (first + (row * no_rectangles + col) * step) % (1 << vmi.BitsPerPixel) ;
      } else {
        red = (red_first + col * step) % (1 << vmi.RedMaskSize);
	      green = (green_first + row * step) % (1 << vmi.GreenMaskSize);
	      blue = (blue_first + (col + row) * step) % (1 << vmi.BlueMaskSize);
        
        color = (red << vmi.RedFieldPosition) | 
                (green << vmi.GreenFieldPosition) | 
                (blue << vmi.BlueFieldPosition);
      }

      if (vg_draw_rectangle(col * width, row * height, width, height, color) != OK) { return !OK; }
      
    }
  }

  return OK;
}

int (vg_draw_sprite)(uint8_t * sprite, xpm_image_t img, uint16_t x, uint16_t y) {
  int bytes_per_pixel = vmi.BytesPerScanLine / vmi.XResolution;
  uint32_t color;

  bzero(video_mem, vmi.BytesPerScanLine * vmi.YResolution);

  for (int row = 0; row < img.height; row++) {
    for (int col = 0; col < img.width; col++) {
      memcpy(&color, sprite + (col + row * img.width), bytes_per_pixel);

      if (vg_draw_pixel(x + col, y + row, color) != OK) {
        return !OK;
      }
    }
  }
  return OK;
}

uint32_t (set_bits)(uint8_t start, uint8_t end) {
  uint32_t bits = 0x0;
  for (int i = start; i < end; i++) { bits |= BIT(i); }
  return bits;
}
