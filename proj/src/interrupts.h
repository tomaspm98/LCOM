#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include <lcom/lcf.h>
#include <stdint.h>
#include "timer/timer.h"
#include "keyboard/keyboard.h"
#include "piece.h"
#include "ball.h"
#include "graphics/video_gr.h"
#include "colors.h"
#include "mouse/mouse.h"

int subscribe_interrupts();
int unsubscribe_interrupts();
int interrupts();
void handle_keys();

#endif
