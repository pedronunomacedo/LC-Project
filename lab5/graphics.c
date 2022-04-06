#include <graphics.h>

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
