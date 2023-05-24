#include <lcom/lcf.h>
#include <string.h>
#include "timer/timer.h"
#include "keyboard/keyboard.h"
#include "graphics/video_gr.h"
#include "timer/i8254.h"
#include "colors.h"
#include "entity.h"
#include "logic.h"
#include "images/transferir.xpm"
#include "images/nada.xpm"
#include "images/piece.xpm"

uint8_t irq_set_timer=0;
uint8_t irq_set_kbd=1;
Entity* teste;
extern uint8_t scancode;
extern int timer_irq_counter;
int piece_1_x = 30;
int piece_1_y = 255;
int piece_2_x = 770;
int piece_2_y = 255;
int ball_x = 390;
int ball_y = 290;
int w_key_state = KEY_STATE_RELEASED;
int s_key_state = KEY_STATE_RELEASED;
int up_key_state = KEY_STATE_RELEASED;
int down_key_state = KEY_STATE_RELEASED;


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
    if (vg_init(0x115)) return 1;
    //sprites
    //falta interrupts mouse+rtc+serial port
    if (timer_subscribe_int(&irq_set_timer)) return 1;
    if(keyboard_subscribe_interrupts(&irq_set_kbd)) return 1; 
    //teste = create_sprite(transferir_xpm);
    allocateImgBuffer();
    allocateDrawBuffer();

    return 0;
}

int end(){
    if (vg_exit()) return 1;
    //terminar sprites
    //falta interrupts mouse+rtc+serial port
    if (timer_unsubscribe_int()) return 1;
    if(keyboard_unsubscribe_interrupts()) return 1;
     freeDrawBuffer();
     //freeImBuffer();
    //destroy_sprite(teste);
    //freeImBuffer();
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
                    if (scancode==KBC_MAKE_W_KEY){
                        w_key_state = KEY_STATE_PRESSED;
                    }
                    if (scancode==KBC_BREAK_W_KEY){
                        w_key_state = KEY_STATE_RELEASED;
                    }
                    if (scancode==KBC_MAKE_S_KEY){
                        s_key_state = KEY_STATE_PRESSED;
                    }
                    if (scancode==KBC_BREAK_S_KEY){
                        s_key_state = KEY_STATE_RELEASED;
                    }
                    if (scancode==KBC_MAKE_UP_KEY){
                        up_key_state = KEY_STATE_PRESSED;
                    }
                    if (scancode==KBC_BREAK_UP_KEY){
                        up_key_state = KEY_STATE_RELEASED;
                    }
                    if (scancode==KBC_MAKE_DOWN_KEY){
                        down_key_state = KEY_STATE_PRESSED;
                    }
                    if (scancode==KBC_BREAK_DOWN_KEY){
                        down_key_state = KEY_STATE_RELEASED;
                    }
                    if(w_key_state == KEY_STATE_PRESSED){
                        piece_1_y-=10;
                    }
                    if(s_key_state == KEY_STATE_PRESSED){
                        piece_1_y+=10;
                    }
                    if(up_key_state == KEY_STATE_PRESSED){
                        piece_2_y-=10;
                    }
                    if(down_key_state == KEY_STATE_PRESSED){
                        piece_2_y+=10;
                    }
                }
                if (msg.m_notify.interrupts & BIT(irq_set_timer)){
                  timer_int_handler();
                  if (vg_draw_rectangle(0,0,800,30,BLUE)) return 1;
                  if (vg_draw_rectangle(0,570,800,30,BLUE)) return 1;
                  if (vg_draw_rectangle(398,0,4,600,BLUE)) return 1;   
                  if (draw_xpm((xpm_map_t) piece_xpm,piece_1_x,piece_1_y)) return 1; 
                  if (draw_xpm((xpm_map_t) piece_xpm,piece_2_x,piece_2_y)) return 1;
                  if (draw_xpm((xpm_map_t) ball_xpm,ball_x,ball_y)) return 1;
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

    



  if (end()) return 1;

  printf("FEZ TUDO");

  return 0;
  
}
