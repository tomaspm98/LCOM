#include "mouse.h"

int mouse_hook_id = 3;

int mouse_subscribe_int(uint8_t *bit_no) {
  if(bit_no == NULL) return 1;
  *(bit_no) = (uint8_t) mouse_hook_id;

    if(sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id) != 0) {
    printf("Error:sys_irqsetpolicy fail \n");
    return 1;
  }
  //Worked
  return 0;
}

int mouse_unsubscribe_int() {
  if(sys_irqrmpolicy(&mouse_hook_id) != 0) {
    printf("Error:sys_irqrmpolicy fail\n");
    return 1;
  }
    //Worked
  return 0;
}

void (delay)(int cycles) {
  while(cycles) {
    tickdelay(micros_to_ticks(WAIT_KBC));
    cycles--;
  }
}
int mouse_read(){
    uint8_t controller_status, mouse_data;
    int timeout_counter = MAX_ATTEMPS;

    while (timeout_counter) {
        if (util_sys_inb(KBC_STATUS_REG, &controller_status)) {
            printf("Error: mouse_read: Failed to read PS/2 controller status\n");
            return 1;
        }

        if (controller_status & FULL_OUT_BUFFER) {
            if (util_sys_inb(KBC_OUT_CMD, &mouse_data)) {
                printf("Eroor: mouse_read: Failed to read keyboard data\n");
                return 1;
            }

            if (!(controller_status & (PARITY_ERROR | TIMEOUT_ERROR))) {
                return mouse_data;
            } else {
                printf("Error: mouse_read: Parity and/or time-out error\n");
                return 1;
            }
        }

        delay(1);
        timeout_counter--;
    }

    printf("Mouse: read_mouse: Timed out\n");
    return 1;
}

int mouse_write(uint8_t cmd, uint8_t port){
    uint8_t counter = MAX_ATTEMPS;
    uint8_t status, info;

    while(counter){
        if(util_sys_inb(KBC_STATUS_REG, &status)){
            return 1;
        }
        if(status & FULL_OUT_BUFFER){
            if(util_sys_inb(KBC_OUT_CMD, &info) != 0){
                return 1;
            }
        }
        if(!(status * FULL_IN_BUFFER)){
            if(sys_outb(port,cmd) != 0){
                return 1;
            }
            delay(1);
            return 0;
        }
        delay(1);
        counter--;
    }
    return 1;
}

int mouse_command(uint8_t cmd){
    uint8_t data;

    do{
        if(mouse_write(cmd, FULL_OUT_BUFFER) != 0){
        return 1;
        }
        data = mouse_read();

    } while (data == 0xFE);
    if (data == 0xFA){
        return 0;
    }
    return 1;

}

int mouse_discard(){
    uint8_t status;
    int counter = MAX_ATTEMPS;

    while(counter){
        if(util_sys_inb(KBC_STATUS_REG, &status) != 0) return 1;
        delay(1);
        counter--
    }
    return 0;
}
