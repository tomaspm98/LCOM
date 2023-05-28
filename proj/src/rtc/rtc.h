#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>

// Macros
#define IRQ_RTC             8

#define RTC_IN              0x70
#define RTC_OUT             0x71
#define REG_B               0x0B

#define BINARY              BIT(2)
#define UPDATING            BIT(7)

#define RTC_SECONDS         0
#define RTC_MINUTES         2
#define RTC_HOURS           4
#define RTC_DAY             7
#define RTC_MONTH           8
#define RTC_YEAR            9

#define REGISTER_UPDATING   10
#define REGISTER_COUNTING   11

// Functions
int rtc_startup();
int rtc_subscribe_intrpt();
int rtc_unsubscribe_intrpt();
int rtc_ih();
int rtc_read(uint8_t command, uint8_t *output);
int rtc_is_updating();
int rtc_is_binary();
int rtc_update_time();
uint8_t to_binary(uint8_t bcd_number);
int rtc_ih();

#endif
