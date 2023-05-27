#include <lcom/lcf.h>
#include "kbc.h"
#include "timer/i8254.h"
#include "keyboard.h"

#include <stdint.h>

#include "i8042.h"

int keyboard_hook_id = 1;
uint8_t scancode;

int (keyboard_subscribe_intrpt)(uint8_t *bit_no){
    if (bit_no == NULL) return 1;
    *bit_no = keyboard_hook_id;
    return sys_irqsetpolicy(IRQ_KEYBOARD, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id);
    
}

int (keyboard_unsubscribe_intrpt)(){
   return sys_irqrmpolicy(&keyboard_hook_id);
}

void (kbc_ih)(){
   uint8_t status;
   kbc_read_stat(&status);
   if ((status & (PARITY_ERROR|TIMEOUT_ERROR))!=0) return;
   util_sys_inb(KBC_OUT_CMD, &scancode);
}



