#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include <keyboard.h>

#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
	// sets the language of LCF messages (can be either EN-US or PT-PT)
	lcf_set_language("EN-US");

	// enables to log function invocations that are being "wrapped" by LCF
	// [comment this out if you don't want/need it]
	lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

	// enables to save the output of printf function calls on a file
	// [comment this out if you don't want/need it]
	lcf_log_output("/home/lcom/labs/lab3/output.txt");

	// handles control over to LCF
	// [LCF handles command line arguments and invokes the right function]
	if (lcf_start(argc, argv))
		return 1;

	// LCF clean up tasks
	// [must be the last statement before return]
	lcf_cleanup();

	return 0;
}

int(kbd_test_scan)() {

	int ipc_status, r;
  	message msg;

	uint8_t kbd_bit_no;
	kbd_subscribe_int(&kbd_bit_no);
	uint8_t kbd_irq_set = BIT(kbd_bit_no);

	while( 1 ) {
    
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { 
      	switch (_ENDPOINT_P(msg.m_source)) {
          	case HARDWARE: 
				if (msg.m_notify.interrupts & kbd_irq_set) {
					 
				}
				break;
			default:
				break; 
		}
		}
	}

	kbd_unsubscribe_int();

	return 1;
}

int(kbd_test_poll)() {
	/* To be completed by the students */
	printf("%s is not yet implemented!\n", __func__);

	return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
	/* To be completed by the students */
	printf("%s is not yet implemented!\n", __func__);

	return 1;
}
