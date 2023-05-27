#include "interrupts.h"

uint8_t irq_set_timer=0;
uint8_t irq_set_kbd=1;
extern uint8_t scancode;
extern int timer_irq_counter;
int w_key_state = KEY_STATE_RELEASED;
int s_key_state = KEY_STATE_RELEASED;
int up_key_state = KEY_STATE_RELEASED;
int down_key_state = KEY_STATE_RELEASED;
extern int piece_1_x;
extern int piece_1_y;
extern int piece_2_x;
extern int piece_2_y;
extern int goal_left;
extern int goal_right;

int subscribe_interrupts(){
    if (timer_subscribe_int(&irq_set_timer)) return 1;
    if(keyboard_subscribe_interrupts(&irq_set_kbd)) return 1;
    //falta mouse

    return 0;
}

int unsubscribe_interrupts(){
    if (timer_unsubscribe_int()) return 1;
    if(keyboard_unsubscribe_interrupts()) return 1;
    //falta mouse

    return 0;
}

int interrupts(){
    int r, ipc_status;
  message msg;

  while(scancode != BREAK_ESC && goal_left<3 && goal_right<3) { /* You may want to use a different condition */
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
                            move_piece1_up();
                        }
                    }
                    if(s_key_state == KEY_STATE_PRESSED){
                        if (piece_1_y<=UPPER_LIMIT){
                            move_piece1_down();
                        }
                    }
                    if(up_key_state == KEY_STATE_PRESSED){
                        if(piece_2_y>=LOWER_LIMIT){
                            move_piece2_up();
                        }
                    }
                    if(down_key_state == KEY_STATE_PRESSED){
                        if (piece_2_y<=UPPER_LIMIT){
                            move_piece2_down();
                        }
                    }
                }
                if (msg.m_notify.interrupts & BIT(irq_set_timer)){
                  timer_int_handler();
                  switch(goal_right){
                    case 0:
                        if(draw_xpm((xpm_map_t)zero_xpm,365,40)) return 1;
                        break;
                    case 1:
                        if(draw_xpm((xpm_map_t)one_xpm,365,40)) return 1;
                        break;
                    case 2:
                        if(draw_xpm((xpm_map_t)two_xpm,365,40)) return 1;
                        break;
                    case 3:
                        if(draw_xpm((xpm_map_t)three_xpm,365,40)) return 1;
                        break; 
                    default:
                        return 1;       
                  }

                  switch(goal_left){
                    case 0:
                        if(draw_xpm((xpm_map_t)zero_xpm,405,40)) return 1;
                        break;
                    case 1:
                        if(draw_xpm((xpm_map_t)one_xpm,405,40)) return 1;
                        break;
                    case 2:
                        if(draw_xpm((xpm_map_t)two_xpm,405,40)) return 1;
                        break;
                    case 3:
                        if(draw_xpm((xpm_map_t)three_xpm,405,40)) return 1;
                        break; 
                    default:
                        return 1;       
                  }
                  if (vg_draw_rectangle(0,0,800,35,BLUE)) return 1;
                  if (vg_draw_rectangle(0,565,800,35,BLUE)) return 1;
                  if (vg_draw_rectangle(398,0,4,600,BLUE)) return 1;   
                  if (draw_piece_1()) return 1;
                  if (draw_piece_2()) return 1;
                  if (draw_ball()) return 1;
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

 return 0;

}
