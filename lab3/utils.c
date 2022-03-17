#include <lcom/lcf.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
	/* To be completed by the students */
	printf("%s is not yet implemented!\n", __func__);

	return !OK;
}

int(util_get_MSB)(uint16_t val, uint8_t *lsb) {
	/* To be completed by the students */
	printf("%s is not yet implemented!\n", __func__);

	return !OK;
}

int(util_sys_inb)(int port, uint8_t *value) {
	uint32_t byte;
	int ret = sys_inb(port,&byte);

	*value = (uint8_t)byte;

	return ret;
}
