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
#include <stdlib.h>

uint8_t irq_set_timer=0;
uint8_t irq_set_kbd=1;
Entity* teste;
extern uint8_t scancode;
extern int timer_irq_counter;
int piece_1_x = 30;
int piece_1_y = 255;
int piece_2_x = 757;
int piece_2_y = 255;
int ball_x = 390;
int ball_y = 290;
int w_key_state = KEY_STATE_RELEASED;
int s_key_state = KEY_STATE_RELEASED;
int up_key_state = KEY_STATE_RELEASED;
int down_key_state = KEY_STATE_RELEASED;
bool not_random = false;
int r=-1;
bool startBall = true;
int ball_var_y;
int ball_var_x;



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

void ball_movement(){
   if (startBall){ 
    if (!not_random){
        srand(time(NULL));
        r = rand() % 2;
        not_random = true;
    }
         if (r == 0 && ball_x>=50){
                ball_x-=5;
         }
         else {
            if(r==1 && ball_x<=731){
                ball_x+=5;
                
         }
    }
    if (ball_x == 45 || ball_x== 735){ 
        startBall = false;
    }

   }


   //ver lcombola.txt pra tratar movimentação
   if (ball_x == 45){
    int meio = piece_1_y + 46-11;
    int topo_1 = piece_1_y-11+36;
    int topo_2 = piece_1_y-11+26;
    int topo_3 = piece_1_y-11+16;
    int topo_4 = piece_1_y-11+6;
    int topo_5 = piece_1_y-12;
    int baixo_1 = piece_1_y-11+46;
    int baixo_2 = piece_1_y-11+56;
    int baixo_3 = piece_1_y-11+66;
    int baixo_4 = piece_1_y-11+76;
    int baixo_5 = piece_1_y-11+86;
    int baixo_6 = piece_1_y - 11 + 96; 
     //45 - meio da barra e 10 metade da bola
    if (ball_y == meio){
        ball_var_y=0;
        ball_var_x=5;
    }
    else if (ball_y<meio && ball_y>=topo_1){
        ball_var_x=5;
        ball_var_y=-1; 
    }

    else if (ball_y<topo_1 && ball_y>=topo_2){
        ball_var_x=5;
        ball_var_y=-2; 
    }

    else if (ball_y<topo_2 && ball_y>=topo_3){
        ball_var_x=5;
        ball_var_y=-3; 
    }

    else if (ball_y<topo_3 && ball_y>=topo_4){
        ball_var_x=5;
        ball_var_y=-4; 
    }
    else if (ball_y<topo_4 && ball_y>=topo_5){
        ball_var_x=5;
        ball_var_y=-5; 
    }
    else if (ball_y>meio && ball_y<=baixo_1){
        ball_var_x=5;
        ball_var_y=1; 
    }
    else if (ball_y>baixo_1 && ball_y<=baixo_2){
        ball_var_x=5;
        ball_var_y=2; 
    }
    else if (ball_y>baixo_2 && ball_y<=baixo_3){
        ball_var_x=5;
        ball_var_y=3; 
    }
    else if (ball_y>baixo_3 && ball_y<=baixo_4){
        ball_var_x=5;
        ball_var_y=4; 
    }
    else if (ball_y>baixo_4 && ball_y<=baixo_5){
        ball_var_x=5;
        ball_var_y=5; 
    }
    else if (ball_y>baixo_5 && ball_y<=baixo_6){
        ball_var_x=5;
        ball_var_y=6; 
    }

    
   }
   if (ball_x == 735){
    int meio = piece_2_y +46-11;
    int topo_1 = piece_2_y-11+36;
    int topo_2 = piece_2_y-11+26;
    int topo_3 = piece_2_y-11+16;
    int topo_4 = piece_2_y-11+6;
    int topo_5 = piece_2_y-12;
    int baixo_1 = piece_2_y-11+46;
    int baixo_2 = piece_2_y-11+56;
    int baixo_3 = piece_2_y-11+66;
    int baixo_4 = piece_2_y-11+76;
    int baixo_5 = piece_2_y-11+86;
    int baixo_6 = piece_2_y - 11 + 96; 
    if (ball_y == meio){
        ball_var_y=0;
        ball_var_x=-5;
    }
    else if (ball_y<meio && ball_y>=topo_1){
        ball_var_x=-5;
        ball_var_y=-1; 
    }
    

    else if (ball_y<topo_1 && ball_y>=topo_2){
        ball_var_x=-5;
        ball_var_y=-2; 
    }

    else if (ball_y<topo_2 && ball_y>=topo_3){
        ball_var_x=-5;
        ball_var_y=-3; 
    }

    else if (ball_y<topo_3 && ball_y>=topo_4){
        ball_var_x=-5;
        ball_var_y=-4; 
    }

    else if (ball_y>meio && ball_y<=baixo_1){
        ball_var_x=-5;
        ball_var_y=1; 
    }
    else if (ball_y>baixo_1 && ball_y<=baixo_2){
        ball_var_x=-5;
        ball_var_y=2; 
    }
    else if (ball_y>baixo_2 && ball_y<=baixo_3){
        ball_var_x=-5;
        ball_var_y=3; 
    }
    else if (ball_y>baixo_3 && ball_y<=baixo_4){
        ball_var_x=-5;
        ball_var_y=4; 
    }
    else if (ball_y>baixo_4 && ball_y<=baixo_5){
        ball_var_x=-5;
        ball_var_y=5; 
    }
    else if (ball_y>baixo_5 && ball_y<=baixo_6){
        ball_var_x=-5;
        ball_var_y=6; 
    }
    else if (ball_y<topo_4 && ball_y>=topo_5){
        ball_var_x=5;
        ball_var_y=-5; 
    }
    
   }
   if ((ball_y>=34 && ball_y<=40) || (ball_y >= 540 && ball_y<=546)){
    if(ball_var_x<0){
        ball_var_x = -5;
        ball_var_y = -ball_var_y;
    }
    else {
        ball_var_x = 5;
        ball_var_y = -ball_var_y;
    }
   }
   
   ball_x+=ball_var_x;
   ball_y+=ball_var_y;
   
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
                        if(piece_1_y>=LOWER_LIMIT){
                            piece_1_y-=20;
                        }
                    }
                    if(s_key_state == KEY_STATE_PRESSED){
                        if (piece_1_y<=UPPER_LIMIT){
                            piece_1_y+=20;
                        }
                    }
                    if(up_key_state == KEY_STATE_PRESSED){
                        if(piece_2_y>=LOWER_LIMIT){
                            piece_2_y-=20;
                        }
                    }
                    if(down_key_state == KEY_STATE_PRESSED){
                        if (piece_2_y<=UPPER_LIMIT){
                            piece_2_y+=20;
                        }
                    }
                }
                if (msg.m_notify.interrupts & BIT(irq_set_timer)){
                  timer_int_handler();
                  if (vg_draw_rectangle(0,0,800,35,BLUE)) return 1;
                  if (vg_draw_rectangle(0,565,800,35,BLUE)) return 1;
                  if (vg_draw_rectangle(398,0,4,600,BLUE)) return 1;   
                  if (draw_xpm((xpm_map_t) piece_xpm,piece_1_x,piece_1_y)) return 1; 
                  if (draw_xpm((xpm_map_t) piece_xpm,piece_2_x,piece_2_y)) return 1;
                  if (draw_xpm((xpm_map_t) ball_xpm,ball_x,ball_y)) return 1;
                  ball_movement();
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
