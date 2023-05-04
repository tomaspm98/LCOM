#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include <lcom/lab2.h>

#include <minix/sysutil.h>

#include "keyboard.h"
#include "kbc.h"
#include "i8042.h"

#include <stdbool.h>
#include <stdint.h>

#define T0_FREQ 60

extern uint8_t scancode;
extern int keyboard_hook_id;
extern int counter_KBC;
extern int timer_hook_id;
extern int timer_irq_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}



int(kbd_test_scan)() {
 uint8_t irq_set;
 int ipc_status,r;
 message msg;
 int size;
 uint8_t ext_scancode[2];

 if (keyboard_subscribe_interrupts(&irq_set)) return 1;

 while(scancode != BREAK_ESC) { /* You may want to use a different condition */
     /* Get a request message. */
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & BIT(irq_set)) { /* subscribed interrupt */
                    kbc_ih();
                    if (scancode == 0xE0){
                      size = 2;
                      ext_scancode[1] = scancode;
                      kbc_ih();
                      ext_scancode[0] = scancode;
                    }
                    else {
                      size = 1;
                       ext_scancode[1] = 0;
                       ext_scancode[0] = scancode;
                    }

                    if (scancode & MAKE_CODE){
                      kbd_print_scancode(false,size,ext_scancode);
                    }
                    else {
                      kbd_print_scancode(true,size,ext_scancode);
                    }
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }

 if (keyboard_unsubscribe_interrupts()) return 1;

  return 0;
}

  


int(kbd_test_poll)() {
   uint8_t ext_scancode[2];
   int size;
   uint8_t status;

   while (scancode != BREAK_ESC){
      if (read_KBC_status(&status)) return 1;
      kbc_ih();
      if (scancode == 0x0E){
        size = 2;
        ext_scancode[1] = scancode;
        kbc_ih();
        ext_scancode[0] = scancode;
      }
      else {
        size = 1;
         ext_scancode[1]=0;
         ext_scancode[0]=scancode;
      }
      if (scancode & MAKE_CODE){
        kbd_print_scancode(false, size, ext_scancode);
      } else {
        kbd_print_scancode(true, size, ext_scancode);
      }
   }

   if (kbc_restore()) return 1;
   return 0;
}


int(kbd_test_timed_scan)(uint8_t n) {
  uint8_t irq_set_tim, irq_set_kbd;
  int aux_counter = 0;
  int ipc_status, r, size;
  uint8_t ext_scancode[2];
  message msg;

  if (timer_subscribe_int(&irq_set_tim)) return 1;

  if (keyboard_subscribe_interrupts(&irq_set_kbd)) return 1;

  while(scancode != BREAK_ESC && aux_counter<=n) { /* You may want to use a different condition */
     /* Get a request message. */
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & BIT(irq_set_kbd)) { /* subscribed interrupt */
                    kbc_ih();
                    if (scancode == 0xE0){
                      size = 2;
                      ext_scancode[1] = scancode;
                      kbc_ih();
                      ext_scancode[0] = scancode;
                    }
                    else {
                      size = 1;
                       ext_scancode[1] = 0;
                       ext_scancode[0] = scancode;
                    }

                    if (scancode & MAKE_CODE){
                      kbd_print_scancode(false,size,ext_scancode);
                    }
                    else {
                      kbd_print_scancode(true,size,ext_scancode);
                    }
                    aux_counter = 0;
                    timer_irq_counter=0;
                }

                if (msg.m_notify.interrupts & BIT(irq_set_tim)){
                  if ((timer_irq_counter%60)==0){
                    aux_counter++;
                  }
                  timer_int_handler();
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }

 if (keyboard_unsubscribe_interrupts()) return 1;
 if (timer_unsubscribe_int()) return 1;

 return 0;

}
