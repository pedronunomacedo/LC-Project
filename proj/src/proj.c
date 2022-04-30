#include <lcom/lcf.h>
#include <lcom/proj.h>

#include "lib/devices/timer.h"
#include "lib/devices/kbc.h"
#include "lib/devices/graphics.h"
#include "lib/devices/vbe.h"

#include "events/events.h"
#include "menu/main_menu.h"
#include "lib/sprite/sprite.h"

#define FPS 60

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

	if (set_mouse_data_reporting(true) != OK) { return !OK; }

	if (timer_set_frequency(TIMER_SEL0, FPS) != OK) { return !OK; }

	uint8_t timer_bit_no, keyboard_bit_no, mouse_bit_no;
	timer_subscribe_int(&timer_bit_no);
	kbd_subscribe_int(&keyboard_bit_no);
	mouse_subscribe_int(&mouse_bit_no);
	uint32_t timer_irq_set = BIT(timer_bit_no), 
				keyboard_irq_set = BIT(keyboard_bit_no),
				mouse_irq_set = BIT(mouse_bit_no);

	int r, ipc_status;
	message msg;
	GAME_STATE game_state = MAIN_MENU;
	
	struct packet mouse_pp;

	if (initialize_main_menu(400,400) != OK) { return !OK; }

	while( game_state != QUIT ) {
    	if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
			printf("driver_receive failed with: %d", r);
			continue;
    	}

		if (is_ipc_notify(ipc_status)) { 
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: 

					if (msg.m_notify.interrupts & timer_irq_set) {
						timer_int_handler();
						if (draw_main_menu() != OK) { return !OK; }
						vg_swap_buffers();
					}

					if (msg.m_notify.interrupts & keyboard_irq_set) {
						kbd_ih();
						if (check_keyboard_ready()) {
							if (get_keyboard_scancode() == 0x81) {
								game_state = QUIT;
							}
						}
					}

					if (msg.m_notify.interrupts & mouse_irq_set) {
						mouse_ih();
						if (check_mouse_ready()) {
							mouse_pp = get_mouse_packet();
							sprite_set_pos_delta(get_mouse_sprite(), 
													mouse_pp.delta_x,
													mouse_pp.delta_y);
						}
					}
					break;
				default:
					break; 
			}
		}
	}

	sprite_destroy(get_mouse_sprite());

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
