#include <keyboard.h>

static int kbd_hook_id;

int (kbd_subscribe_int)(uint8_t *bit_no) {

	kbd_hook_id = *bit_no = KBD_IRQ;

	if (sys_irqsetpolicy(KBD_IRQ, (IRQ_ENABLE | IRQ_EXCLUSIVE), &kbd_hook_id) != OK) {
		printf("Keyboard sys_irqsetpolicy failed\n");
		return !OK;
	}
	return OK;
}

int (kbd_unsubscribe_int)() {
	if (sys_irqrmpolicy(&kbd_hook_id) != OK) {
		printf("Keyboard sys_irqsetpolicy failed\n");
		return !OK;
	}

	return OK;
}

void (kbc_ih)(void) {

}
