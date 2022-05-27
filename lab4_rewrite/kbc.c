#include "kbc.h"

static int mouse_hook_id;

int (mouse_subscribe_int)(uint8_t * bit_no)  {
    if (bit_no == NULL) { return !OK; }
    *bit_no = mouse_hook_id = MOUSE_IRQ;
    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int (mouse_unsubscribe_int)() {
    return sys_irqrmpolicy(&mouse_hook_id);
}

int (get_status_register)(uint8_t * st) {
    return util_sys_inb(KBC_READ_ST_REG, st);
}

void wait_for_IBF() {
    uint8_t st;
    get_status_register(&st);
    while (st & BIT(1)) {
        tickdelay(micros_to_ticks(20000));
        get_status_register(&st);
    }
}

int (set_mouse_data_reporting)(bool enable) {
    uint8_t cmd = (enable) ? 
        KBC_ENABLE_MOUSE_DATA_REPORTING :
        KBC_DISABLE_MOUSE_DATA_REPORTING;

    wait_for_IBF();
    if (sys_outb(KBC_CTRL_REG, KBC_WRITE_BYTE_MOUSE) != OK) { return !OK; }
    wait_for_IBF();
    if (sys_outb(KBC_WRITE_ARGS, cmd) != OK) { return !OK; }

    uint8_t ack;
    if (util_sys_inb(KBC_OUT_BUF, &ack) != OK) { return !OK; }
    if (ack != 0xfa) {
        return set_mouse_data_reporting(enable);
    }
    return OK;
}

static uint8_t data;
static bool error = false;

void (mouse_ih)(void) {
    uint8_t st;
    get_status_register(&st);
    error = false;

    if ((st & BIT(0)) && (st & BIT(5))) {
        if (util_sys_inb(KBC_OUT_BUF, &data) != OK) { return; }

        if ((st & BIT(7)) || (st & BIT(6))) { error = true; }
    }
    return;
}

uint8_t get_mouse_data() { return data; }

bool check_mouse_error() { return error; }

int assemble_mouse_packet(uint8_t *mouse_data, struct packet *pp) {
    bzero(pp, sizeof(struct packet));

    memcpy(pp->bytes, mouse_data, 3);
    pp->lb = mouse_data[0] & BIT(0);
    pp->rb = mouse_data[0] & BIT(1);
    pp->mb = mouse_data[0] & BIT(2);
    pp->delta_x = (mouse_data[0] & BIT(4)) ? 0xff00 | mouse_data[1] : mouse_data[1];
    pp->delta_y = (mouse_data[0] & BIT(5)) ? 0xff00 | mouse_data[2] : mouse_data[2];
    pp->x_ov = mouse_data[0] & BIT(6);
    pp->y_ov = mouse_data[0] & BIT(7);

    return OK;
}
