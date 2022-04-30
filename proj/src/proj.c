#include <lcom/lcf.h>
#include <lcom/proj.h>

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
	int r, ipc_status;
	message msg;
	uint32_t irq_set = 0;

	while( 1 ) {
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
}
