#pragma once

#include <lcom/lcf.h>

#define DELAY 2000
#define RTC_IRQ 8

#define RTC_ADDR_REG 0x70 //loaded with the address of the RTC
#define RTC_DATA_REG 0x71 //used to transfer data to/from RTC's register

#define RTC_SECONDS 0
#define RTC_SECONDS_ALARM 1
#define RTC_MINUTES 2
#define RTC_MINUTES_ALARM 3
#define RTC_HOURS 4 // 12/24 mode
#define RTC_HOURS_ALARM 5 // 12/24 mode
#define RTC_DAY_WEEK 6 //sunday = 1
#define RTC_DAY_MONTH 7
#define RTC_MONTH 8
#define RTC_YEAR 9
#define RTC_REG_A 10
#define RTC_REG_B 11
#define RTC_REG_C 12
#define RTC_REG_D 13

#define RTC_BASE_YEAR 2000

#define RTC_UIP BIT(7)
#define RTC_UF BIT(4)
#define RTC_UIE BIT(4)
#define RTC_AIE BIT(5)
#define RTC_PIE BIT(6)
#define RTC_DM BIT(2)

int (rtc_subscribe_int)(uint8_t * bit_no);

int (rtc_unsubscribe_int)();

int (rtc_read_register)(uint8_t reg, uint8_t * input);

int (rtc_write_register)(uint8_t reg, uint8_t output);

void (wait_valid_rtc)(void);

void (rtc_ih)(void);

void handle_update_int(void);

int (rtc_disable_all_interrupts)(void);

int (rtc_enable_update_interrupts)(void);
