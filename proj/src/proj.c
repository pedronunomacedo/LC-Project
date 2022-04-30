#include <lcom/lcf.h>
#include <lcom/proj.h>

#include "lib/devices/timer.h"
#include "lib/devices/kbc.h"
#include "lib/devices/graphics.h"
#include "lib/devices/vbe.h"

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

	uint8_t timer_bit_no, keyboard_bit_no, mouse_bit_no;
	if (timer_subscribe_int(&timer_bit_no) != OK || 
			kbd_subscribe_int(&keyboard_bit_no) != OK ||
			mouse_subscribe_int(&mouse_bit_no) != OK) {
		printf("proj_main_loop: subscribe failed");
		return !OK;
	}
	if (set_mouse_data_reporting(true) != OK) {
		printf("proj_main_loop: set_mouse_data_reporting(true) failed");
		return !OK;
	}

	int r, ipc_status;
	message msg;
	uint32_t irq_set = 0;

	while( 0 ) {
    	if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
			printf("driver_receive failed with: %d", r);
			continue;
    	}

		if (is_ipc_notify(ipc_status)) { 
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: 
					if (msg.m_notify.interrupts & irq_set) {
						
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
		printf("proj_main_loop: unsubscribe failed");
		return !OK;
	}
	if (set_mouse_data_reporting(false) != OK) {
		printf("proj_main_loop: set_mouse_data_reporting(false) failed");
		return !OK;
	}
	vg_exit();
	return OK;
}
