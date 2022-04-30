#include <lcom/lcf.h>
#include <lcom/proj.h>

#include "lib/devices/timer.h"
#include "lib/devices/kbc.h"
#include "lib/devices/graphics.h"
#include "lib/devices/vbe.h"

#include "events/events.h"

int main(int argc, char *argv[]) {
	lcf_set_language("EN-US");
	lcf_trace_calls("/home/lcom/labs/proj/trace.txt");
	lcf_log_output("/home/lcom/labs/proj/output.txt");
	if (lcf_start(argc, argv)) 
		return !OK;
	lcf_cleanup();
	return OK;
}

int (proj_main_loop)(int argc, char *argv[]) {
	if (vg_init(MODE_RES_1152x864_BITS_32) != OK) { return !OK; }

	if (set_mouse_data_reporting(true) != OK) {
		printf("proj_main_loop: set_mouse_data_reporting(true) failed\n");
		return !OK;
	}

	uint8_t timer_bit_no, keyboard_bit_no, mouse_bit_no;
	if (timer_subscribe_int(&timer_bit_no) != OK || 
			kbd_subscribe_int(&keyboard_bit_no) != OK ||
			mouse_subscribe_int(&mouse_bit_no) != OK) {
		printf("proj_main_loop: subscribe failed\n");
		return !OK;
	}
	uint32_t timer_irq_set = BIT(timer_bit_no), 
				keyboard_irq_set = BIT(keyboard_bit_no),
				mouse_irq_set = BIT(mouse_bit_no);

	int r, ipc_status;
	message msg;
	GAME_STATE game_state = MAIN_MENU;

	while( game_state != QUIT ) {
    	if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
			printf("driver_receive failed with: %d", r);
			continue;
    	}

		if (is_ipc_notify(ipc_status)) { 
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: 

					if (msg.m_notify.interrupts & timer_irq_set) {
						game_state = QUIT; //TODO: handle timer interrupt
					}

					if (msg.m_notify.interrupts & keyboard_irq_set) {
						game_state = QUIT; //TODO: handle keyboard interrupt
					}

					if (msg.m_notify.interrupts & mouse_irq_set) {
						game_state = QUIT; //TODO: handle mouse interrupt
					}
					break;
				default:
					break; 
			}
		}
	}

	if (mouse_unsubscribe_int() != OK ||
			kbd_unsubscribe_int() != OK ||
			timer_unsubscribe_int() != OK) {
		printf("proj_main_loop: unsubscribe failed\n");
		return !OK;
	}
	if (set_mouse_data_reporting(false) != OK) {
		printf("proj_main_loop: set_mouse_data_reporting(false) failed\n");
		return !OK;
	}
	vg_exit();
	return OK;
}
