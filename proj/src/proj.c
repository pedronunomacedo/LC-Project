#include <lcom/lcf.h>
#include <lcom/proj.h>

#include "lib/devices/timer.h"
#include "lib/devices/kbc.h"
#include "lib/devices/graphics.h"
#include "lib/devices/vbe.h"

#include "events/events.h"
#include "menu/main_menu.h"
#include "menu/rules_menu.h"
#include "menu/pause_menu.h"
#include "game/game_end_menu.h"
#include "game/game.h"
#include "lib/sprite/sprite.h"

#include "assets/game/initializing.xpm"

#define FPS 50

static sprite * init;

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
	if (timer_set_frequency(TIMER_SEL0, FPS) != OK) { return !OK; }
	if (vg_init(MODE_RES_1152x864_BITS_32) != OK) { return !OK; }

	init = sprite_new(initializing_xpm,0,0);
	if (vg_draw_block_sprite_without_checks(init) != OK) { return !OK; }

	if (set_mouse_data_reporting(true) != OK) { return !OK; }

	uint8_t timer_bit_no, keyboard_bit_no, mouse_bit_no;
	if (timer_subscribe_int(&timer_bit_no) != OK) { return !OK; }
	if (kbd_subscribe_int(&keyboard_bit_no) != OK) { return !OK; }
	if (mouse_subscribe_int(&mouse_bit_no) != OK) { return !OK; }
	uint32_t 	timer_irq_set = BIT(timer_bit_no), 
				keyboard_irq_set = BIT(keyboard_bit_no),
				mouse_irq_set = BIT(mouse_bit_no);

	int r, ipc_status;
	message msg;
	GAME_STATE game_state = MAIN_MENU;
	
	if (initialize_main_menu((WINDOW_WIDTH)/2,(WINDOW_HEIGHT)/3) != OK) { return !OK; }
	if (initialize_rules_menu((WINDOW_WIDTH)/2,(WINDOW_HEIGHT)/3) != OK) { return !OK; }
	if (initialize_pause_menu((WINDOW_WIDTH)/2,(WINDOW_HEIGHT)/3) != OK) { return !OK; }
	if (initialize_game_end_menu() != OK) { return !OK; }
	if (initialize_game() != OK) { return !OK; }

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
						switch (game_state)	{
							case MAIN_MENU:
								game_state=handle_timer_main_menu();
								break;
							case RULES_MENU:
								game_state=handle_timer_rules_menu();
								break;
							case IN_GAME:
								game_state=handle_timer_game();
								break;
							case PAUSE_MENU:
								game_state=handle_timer_pause_menu();
								break;
							case END_GAME:
								game_state=handle_timer_game_end_menu();
								break;
							default:
								break;
						}
					}

					if (msg.m_notify.interrupts & keyboard_irq_set) {
						kbd_ih();
						if (check_keyboard_ready()) {
							switch (game_state) {
								case MAIN_MENU:
									game_state=handle_keyboard_main_menu(get_keyboard_scancode());
									break;
								case RULES_MENU:
									game_state=handle_keyboard_rules_menu(get_keyboard_scancode());
									break;
								case IN_GAME:
									game_state=handle_keyboard_game(get_keyboard_scancode());
									break;
								case PAUSE_MENU:
									game_state=handle_keyboard_pause_menu(get_keyboard_scancode());
									break;
								case END_GAME:
									game_state=handle_keyboard_game_end_menu(
										get_keyboard_scancode());
									break;
								default:
									break;
							}
						}
					}

					if (msg.m_notify.interrupts & mouse_irq_set) {
						mouse_ih();
						if (check_mouse_ready()) {
							switch (game_state) {
								case MAIN_MENU:
									game_state=handle_mouse_main_menu(get_mouse_packet());
									break;
								case RULES_MENU:
									game_state=handle_mouse_rules_menu(get_mouse_packet());
									break;
								case PAUSE_MENU:
									game_state=handle_mouse_pause_menu(get_mouse_packet());
									break;
								default:
									break;
							}
						}
					}
					break;
				default:
					break; 
			}
		}
	}

	destroy_game();
	destroy_game_end_menu();
	destroy_pause_menu();
	destroy_rules_menu();
	destroy_main_menu();

	if (mouse_unsubscribe_int() != OK) { return !OK; }
	if (kbd_unsubscribe_int() != OK) { return !OK; }
	if (timer_unsubscribe_int() != OK) { return !OK; }
	if (set_mouse_data_reporting(false) != OK) { return !OK; }
	
	return vg_exit();
}
