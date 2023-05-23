#include <lcom/lcf.h>
#include <string.h>
#include "timer/timer.h"
#include "keyboard/keyboard.h"
#include "graphics/video_gr.h"
#include "timer/i8254.h"
#include "entity.h"
#include "images/transferir.xpm"

uint8_t irq_set_timer=0;
uint8_t irq_set_kbd=1;
Entity* teste;
extern uint8_t scancode;

int (main)(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/g4/proj/src/debug/trace.txt");
  lcf_log_output("/home/lcom/labs/g4/proj/src/debug/output.txt");
  if (lcf_start(argc, argv)) return 1;
  lcf_cleanup();
  return 0;
}

int start(){
    if (timer_set_frequency(0,GAME_FREQ)) return 1;
    //iniciar buffers video
  
    if(set_graphic_mode(0x115)) return 1;
    //sprites
    //falta interrupts mouse+rtc+serial port
    if (timer_subscribe_int(&irq_set_timer)) return 1;
    if(keyboard_subscribe_interrupts(&irq_set_kbd)) return 1;
    //teste = create_sprite(transferir_xpm);
    displayImage();

    return 0;
}

int end(){
    if (vg_exit()) return 1;
    //terminar sprites
    //falta interrupts mouse+rtc+serial port
    if (timer_unsubscribe_int()) return 1;
    if(keyboard_unsubscribe_interrupts()) return 1;
    destroy_sprite(teste);
    freeImBuffer();
    //desativar interrupts

    return 0;
}

int (proj_main_loop)(int argc, char *argv[]){
  if (start()) return end();

  int r, ipc_status;
  message msg;

  while(scancode != BREAK_ESC) { /* You may want to use a different condition */
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
                }
                if (msg.m_notify.interrupts & BIT(irq_set_timer)){
                  timer_int_handler();
                  displayImage();
                  freeImBuffer();
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }

  //if (draw_xpm((xpm_map_t) transferir_xpm,5,5)) return 1;

  if (end()) return 1;

  printf("FEZ TUDO");

  return 0;
  
}
