#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int timer_irq_counter=0;
int timer_hook_id=0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
     uint8_t status;

     if (timer<0 || timer>2 ||freq>TIMER_FREQ)
        return 1;

    if(timer_get_conf(timer, &status)) return 1;

     status = (status & 0x0f);

     uint8_t controlWord = status | TIMER_LSB_MSB;
     uint8_t timerReg;
     switch(timer){
      case 0:
         controlWord=controlWord | TIMER_SEL0;
         timerReg=TIMER_0;
         break;
      case 1:
         controlWord=controlWord | TIMER_SEL1;
         timerReg=TIMER_1;
         break;
      case 2:
          controlWord=controlWord | TIMER_SEL2;
          timerReg=TIMER_2;
          break;
      default:
          return 1;          
     }

     if (sys_outb(TIMER_CTRL, controlWord)) return 1;

     uint16_t frequency = TIMER_FREQ/freq;

     uint8_t lsb,msb;

     if (util_get_LSB(frequency, &lsb)) return 1;
     if (util_get_MSB(frequency, &msb)) return 1;

     if (sys_outb(timerReg, lsb)) return 1;
     if (sys_outb(timerReg, msb)) return 1;

     return 0;


}

int (timer_subscribe_int)(uint8_t *bit_no) {
    *bit_no=timer_hook_id;
    if (sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE, &timer_hook_id)) return 1;
    return 0;
}

int (timer_unsubscribe_int)() {
  if (sys_irqrmpolicy(&timer_hook_id)) return 1;
  return 0;
  
}

void (timer_int_handler)() {
  timer_irq_counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t timerReg=TIMER_0;
  //faz se limites, dps readback, escreves no registo e les
  
  if (st==NULL || timer<0 || timer>2) {
    return 1;
  } 
  

  uint8_t readBack = TIMER_RB_CMD | TIMER_RB_COUNT_ |TIMER_RB_SEL(timer);
  if (sys_outb(TIMER_CTRL, readBack)) return 1;
  //ou (sys_outb(TIMER_CTRL, readBack)!=0)
  switch(timer){ //em vez disto pra descobrir timerReg fazer timerReg=TIMER_0+timer
    case 0:
      timerReg=TIMER_0;
      break;
    case 1:
      timerReg=TIMER_1;
      break;
    case 2:
       timerReg=TIMER_2;
       break;
    default:
       return 1;       
  }

  if (util_sys_inb(timerReg, st)) return 1;

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  
  if (timer<0 || timer>2)
     return 1;

  union timer_status_field_val value;

  switch(field){  //& faz um and bit a bit
    case  tsf_all: //todos os bits
       value.byte = st;
       break;
    case tsf_initial: //bits 5 e 3
       value.in_mode = (st & 0x30) >> 4;
       break;
    case tsf_mode: //bits 3 2 1
       value.count_mode = (st & 0x0E) >> 1;
       break;
    case tsf_base: //bit 0
       value.bcd = (st & 0x01);
       break;
    default:
       return 1;          
  }   
  
  timer_print_config(timer, field, value);

  return 0;
}
