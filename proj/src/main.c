#include <lcom/lcf.h>
#include <lcom/timer.h>
#include "keyboard/keyboard.h"
#include "graphics/video_gr.h"
#include "timer/i8254.h"

int (main)(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/debug/trace.txt");
  lcf_log_output("/home/lcom/labs/debug/output.txt");
  if (lcf_start(argc, argv)) return 1;
  lcf_cleanup();
  return 0;
}

int start(){
    if (timer_set_frequency(0,TIMER_FREQ)) return 1;
    //iniciar buffers video
    if(set_graphic_mode(0x115)) return 1;
    //sprites
    //falta interrupts mouse+rtc+serial port
    if (timer_subscribe_int()) return 1;
    if(keyboard_subscribe_interrupts()) return 1;

    return 0;


}

int end(){
    if (vg_exit()) return 1;
    //terminar sprites
    //falta interrupts mouse+rtc+serial port
    if (timer_unsubscribe_interrupts()) return 1;
    if(keyboard_unsubscribe_interrupts()) return 1;
    //desativar interrupts

    return 0;
}

/*int loop_game(){

}*/