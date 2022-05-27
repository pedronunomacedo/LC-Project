#include <lcom/lcf.h>

int (util_sys_inb)(int port, uint8_t *value) {
    uint32_t input;
    if (sys_inb(port, &input) != OK) { return !OK; }
    *value = (uint8_t)input;
    return OK;
}
