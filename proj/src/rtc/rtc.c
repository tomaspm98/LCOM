#include "rtc.h"

int rtc_hook_id = 4; 
bool binary_mode;
uint8_t year, month, day, hours, minutes, seconds;

int rtc_startup() {
    uint8_t reg_b;
    
    if(rtc_read(REG_B, &reg_b)) return 1;
    
    reg_b &= ~BIT(7);
    reg_b |= BIT(2);
    reg_b |= BIT(1);

    return 0;
}

int rtc_subscribe_intrpt() {
    return sys_irqsetpolicy(IRQ_RTC, IRQ_REENABLE, &rtc_hook_id);
}

int rtc_unsubscribe_intrpt() {
    return sys_irqrmpolicy(&rtc_hook_id);
}



int rtc_read(uint8_t command, uint8_t *output) {
    if (sys_outb(RTC_IN, command) != 0) return 1;
	if (util_sys_inb(RTC_OUT, output) != 0) return 1;

    return 0;
}

int (rtc_write_reg)(uint8_t reg, uint8_t data) {
    if (sys_outb(RTC_IN, reg)) return 1;
    if (sys_outb(RTC_OUT, data)) return 1;

    return 0;
}

int rtc_is_updating() {
    uint8_t result;
    if (rtc_read(REGISTER_UPDATING, &result)) return 1;

	return result & UPDATING;
}


int rtc_update_time() {
    
    if (rtc_is_updating()) return 1;
    uint8_t output;

    if (rtc_read(RTC_SECONDS, &output) != 0) return 1;
    seconds = output;
    
    if (rtc_read(RTC_MINUTES, &output) != 0) return 1;
    minutes = output;
    
    if (rtc_read(RTC_HOURS, &output) != 0) return 1;
    hours = output;

    if (rtc_read(RTC_DAY, &output) != 0) return 1;
    day = output;

    if (rtc_read(RTC_MONTH, &output) != 0) return 1;
    month = output;

    if (rtc_read(RTC_YEAR, &output) != 0) return 1;
    year = output;

    return 0;
}

int rtc_ih(){
    if (rtc_update_time()) return 1;
    return 0;
    }
