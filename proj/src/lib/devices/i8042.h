#pragma once

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8042 KBC.
 */

//keyboard codes
#define KBC_ESQ_BC 0x81
#define KBC_LEFT_ARROW_MC 0x4be0
#define KBC_RIGHT_ARROW_MC 0x4de0
#define KBC_SPACE_BC 0xb9

//kbc utils
#define DELAY 20000
#define KBC_TWOBYTE_CODE 0xE0
#define KBC_MSB BIT(7) 
#define KBD_IRQ 1
#define MOUSE_IRQ 12

//keyboard status register
#define KBC_ST_REG 0x64 //keyboard status register
#define KBC_OBF BIT(0) //status register output buffer full bit
#define KBC_IBF BIT(1)
#define KBC_SYS BIT(2)
#define KBC_A2 BIT(3)
#define KBC_INH BIT(4)
#define KBC_AUX BIT(5) //status register AUX bit
#define KBC_TIMEOUT_ERR BIT(6) //status register timeout error bit
#define KBC_PARITY_ERR BIT(7) //status register parity error bit

//keyboard addresses
#define KBC_OUT_BUF 0x60 //keyboard output buffer
#define KBC_CMD_REG 0x64 //keyboard command register
#define KBC_ARG_REG 0x60
#define KBC_CMD_RCB 0x20 //keyboard read command byte
#define KBC_CMD_WCB 0x60 //keyboard write command byte

//kbc commands
#define KBC_DISABLE_MOUSE 0xa7
#define KBC_ENABLE_MOUSE 0xa8
#define KBC_CHECK_MOUSE 0xa9
#define KBC_WR_BYTE_MOUSE 0xd4

//kbc control
#define KBC_INT BIT(0) //command byte enable interrupt on keyboard 
#define KBC_INT2 BIT(1)
#define KBC_DIS BIT(4)
#define KBC_DIS2 BIT(5)

//mouse utils
#define MOUSE_READ_RES 0x60
#define MOUSE_ACK 0xfa
#define MOUSE_NACK 0xfe
#define MOUSE_ERROR 0xfc

//mouse info
#define MOUSE_Y_OVFL BIT(7)
#define MOUSE_X_OVFL BIT(6)
#define MOUSE_MSB_Y_DELTA BIT(5)
#define MOUSE_MSB_X_DELTA BIT(4)
#define MOUSE_FLAG BIT(3)
#define MOUSE_MIDDLE_BUTTON BIT(2)
#define MOUSE_RIGHT_BUTTON BIT(1)
#define MOUSE_LEFT_BUTTON BIT(0)

//mouse data reporting commands
#define MOUSE_ENABLE_DATA_REPORTING 0xf4
#define MOUSE_DISABLE_DATA_REPORTING 0xf5

/**@} */
/* EOF */
