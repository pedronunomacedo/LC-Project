#include <keyboard.h>

static int kbdHookID;

int (timer_subscribe_int)(uint8_t *bit_no) {
  kbdHookID = *bit_no = KBD_IRQ; // keyboard IRQ line number = 1

    // Used to subscribe a notification on every interrupt in the input irq_line.
    // (The value returned on *kbdHookID must be used in other calls to specify 
    // the interrupt notification to operate on).
  if (!sys_irqsetpolicy(KBD_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &kbdHookID)) {
      printf("keyboard irq_setolicy failed!\n");
      return 0;
  }
  
  return 1;
}

int (timer_unsubscribe_int)() {
    // Unsubscribes a previous subscription of the interrupt notification 
    // associated with the specified hook_id.
  if (!sys_irqrmpolicy(&kbdHookID)) {
      printf("keyboard irq_rmpolicy failed!\n");
      return 0;
  }

  return 1;
}
