// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "kbc.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
  if (set_mouse_data_reporting(true) != OK) { return !OK; }
  uint8_t bit_no;
  mouse_subscribe_int(&bit_no);
  uint32_t mouse_irq_set = BIT(bit_no);

  int r, ipc_status;
  message msg;
  uint8_t mouse_data[3];
  uint8_t size = 0;
  uint8_t data = 0x0;
  bool is_sync = false;

  while( cnt > 0 ) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: 
              if (msg.m_notify.interrupts & mouse_irq_set) { 
                
                mouse_ih();

                if (check_mouse_error()) { continue; }

                data = get_mouse_data();

                if (size == 0 && (data & BIT(3))) { is_sync = true; }

                if (is_sync) {
                  mouse_data[size] = data;
                  if (size == 2) {
                    cnt--;
                    size = 0;
                    is_sync = false;
                    struct packet pp;
                    if (assemble_mouse_packet(mouse_data, &pp) != OK) { return !OK;}
                    mouse_print_packet(&pp);
                  } else {
                    size++;
                  }
                }

              }
              break;
          default:
              break; 
      }
    }
  }
  mouse_unsubscribe_int();
  return set_mouse_data_reporting(false);
}

int (mouse_test_async)(uint8_t idle_time) {
  if (set_mouse_data_reporting(true) != OK) { return !OK; }
  uint8_t mouse_bit_no;
  uint8_t timer_bit_no;
  mouse_subscribe_int(&mouse_bit_no);
  timer_subscribe_int(&timer_bit_no);
  uint32_t mouse_irq_set = BIT(mouse_bit_no);
  uint32_t timer_irq_set = BIT(timer_bit_no);

  int r, ipc_status;
  message msg;
  uint8_t mouse_data[3];
  uint8_t size = 0;
  uint8_t data = 0x0;
  bool is_sync = false;

  extern unsigned counter;

  while( idle_time * sys_hz() > counter ) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: 
              if (msg.m_notify.interrupts & timer_irq_set) { 
                timer_int_handler();
              }
              if (msg.m_notify.interrupts & mouse_irq_set) { 
                
                mouse_ih();

                if (check_mouse_error()) { continue; }

                data = get_mouse_data();

                if (size == 0 && (data & BIT(3))) { is_sync = true; }

                if (is_sync) {
                  mouse_data[size] = data;
                  if (size == 2) {
                    counter = 0 ;
                    size = 0;
                    is_sync = false;
                    struct packet pp;
                    if (assemble_mouse_packet(mouse_data, &pp) != OK) { return !OK;}
                    mouse_print_packet(&pp);
                  } else {
                    size++;
                  }
                }

              }
              break;
          default:
              break; 
      }
    }
  }
  mouse_unsubscribe_int();
  return set_mouse_data_reporting(false);
}
