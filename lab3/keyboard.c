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

uint8_t data = 0x0;
bool error = false;

void (kbc_ih)(void) {
	uint8_t st;
	if (util_sys_inb(KBC_ST_REG, &st) != OK) {
		printf("Reading Status Register Failed");
		return;
	}

	if (st & KBC_OBF) {
		if (util_sys_inb(KBC_OUT_BUF,&data) != OK) {
			printf("Reading Status Register Failed");
			return;
		}

		if (st & KBC_PARITY_ERR || st & KBC_TIMEOUT_ERR) {
			error = true;
		}
	}
}
