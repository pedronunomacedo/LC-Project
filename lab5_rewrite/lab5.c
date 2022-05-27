#include <lcom/lcf.h>

#include <keyboard.h>
#include <graphics.h>

#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	lcf_set_language("EN-US");

	lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

	lcf_log_output("/home/lcom/labs/lab5/output.txt");

	if (lcf_start(argc, argv))
	return 1;

	lcf_cleanup();

	return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
	if (vg_set_mode(mode) != OK) { return !OK; }
	sleep(delay);
	return vg_exit();
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
uint16_t width, uint16_t height, uint32_t color) {
	if (vg_init_graphics(mode) != OK) { return !OK; }
	if (vg_draw_rectangle(x,y,width,height,color) != OK) { return !OK; }
	wait_for_ESQ();
	return vg_exit();
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
	if (vg_init_graphics(mode) != OK) { return !OK; }
	if (vg_draw_pattern(mode,no_rectangles,first,step) != OK) { return !OK; }
	wait_for_ESQ();
	return vg_exit();
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
	if (vg_init_graphics(0x105) != OK) { return !OK; }
	xpm_image_t img;
	bzero(&img, sizeof(xpm_image_t));
	unsigned char* sprite = xpm_load(xpm,XPM_INDEXED,&img);
	if (vg_draw_sprite(sprite, img, x, y) != OK) { return !OK; }
	wait_for_ESQ();
	return vg_exit();
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
					 int16_t speed, uint8_t fr_rate) {
	return OK;
}

int(video_test_controller)() {
	return OK;
}

