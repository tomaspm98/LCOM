#include <lcom/lcf.h>
#include "timer/timer.h"
#include "keyboard/keyboard.h"
#include "graphics/video_gr.h"
#include "timer/i8254.h"
#include "entity.h"

uint8_t irq_set_timer;

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
    if(keyboard_subscribe_interrupts()) return 1;

    return 0;
}

int end(){
    if (vg_exit()) return 1;
    //terminar sprites
    //falta interrupts mouse+rtc+serial port
    if (timer_unsubscribe_int()) return 1;
    if(keyboard_unsubscribe_interrupts()) return 1;
    //desativar interrupts

    return 0;
}

int (proj_main_loop)(int argc, char *argv[]){
  if (start()) return end();
  
  Entity* myEntity = createEntity(10, 10); // replace 50, 50 with the desired x, y position
  if (myEntity == NULL) return end();
  //caminho do ficheiro = /home/lcom/labs/g4/proj/images/<nome_ficheiro>
  if (addFrameXPM(myEntity, "/home/lcom/labs/g4/proj/src/images/transferir.xpm")) return end(); // replace "path_to_your_image_file" with the path to your image file
  printf("OK4");
  if (renderEntity(myEntity, 0, 10, 20)) return end(); // replace 0, 0 with the desired offset

  free(myEntity); // don't forget to free the memory when you're done
  
  if (end()) return 1;

  printf("FEZ TUDO");

  return 0;
}
