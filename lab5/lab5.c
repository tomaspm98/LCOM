// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <minix/sysutil.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "i8042.h"
#include "i8254.h"
#include "keyboard.h"
#include "video_gr.h"

extern uint8_t scancode;
extern int h_res;
extern int v_res;
extern int colorModel;
extern int bpp;
extern vbe_mode_info_t vbe;
// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
    reg86_t reg;
    memset(&reg,0,sizeof(reg));
    reg.ax = 0x4f02;
    reg.bx = mode | BIT(14);
    reg.intno = 0x10;

    if(sys_int86(&reg)) return 1;
    sleep(delay);
    return vg_exit();
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) { //bytes = (bitsperpixel +7) / 8
  
  vg_init(mode);
  reg86_t reg;
  memset(&reg,0,sizeof(reg));
  reg.ax = 0x4f02;
  reg.bx = mode | BIT(14);
  reg.intno = 0x10;

  if (sys_int86(&reg)) return 1;

  if (vg_draw_rectangle(x,y,width,height,color)) return 1;

  int ipc_status, r;
  uint8_t irq_set;
  message msg;

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

  return vg_exit();
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  
  vg_init(mode);

  reg86_t reg;

  memset(&reg,0,sizeof(reg));

  reg.ax= 0x4f02;
  reg.bx = mode | BIT(14);
  reg.intno = 0x10;

  if (sys_int86(&reg)) return 1;

  int colunas = v_res/no_rectangles;
  int linhas = h_res/no_rectangles;

  for (int i=0;i<no_rectangles;i++){
    for (int j=0;j<no_rectangles;j++){
      uint32_t color;
      if (colorModel == 0x06){
        uint32_t Red = (R(first) + j *step) % (1 << vbe.RedMaskSize);
        uint32_t Green = (G(first) + i *step) % (1 << vbe.GreenMaskSize);
        uint32_t Blue = (B(first) + (i+j) *step) % (1 << vbe.BlueMaskSize);
        color = (Red<<vbe.RedFieldPosition) | (Green<<vbe.GreenFieldPosition) | (Blue<<vbe.BlueFieldPosition);
      }
      else {
        color = (first + (i*no_rectangles +j) * step) % (1 << bpp); //indexed mode
      }

      if (vg_draw_rectangle(j*linhas, i*colunas, linhas, colunas, color)) return 1;
    }
  }

  int ipc_status, r;
  uint8_t irq_set;
  message msg;

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

  return vg_exit();

}
int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  /* To be completed */
  printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
