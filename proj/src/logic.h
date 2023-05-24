#ifndef __LOGIC_H
#define __LOGIC_H

#include <lcom/lcf.h>
#include <stdint.h>

#define KBC_MAKE_A_KEY 0x1e
#define KBC_BREAK_A_KEY 0x9e
#define KBC_MAKE_S_KEY 0x1F
#define KBC_BREAK_S_KEY 0x9f
#define KBC_MAKE_D_KEY 0x20
#define KBC_BREAK_D_KEY 0xa0
#define KBC_MAKE_W_KEY 0x11
#define KBC_BREAK_W_KEY 0x91
#define KBC_MAKE_UP_KEY 0x48
#define KBC_BREAK_UP_KEY 0xC8
#define KBC_MAKE_DOWN_KEY 0x50
#define KBC_BREAK_DOWN_KEY 0xD0
#define UPPER_LIMIT 470
#define LOWER_LIMIT 40

#define KEY_STATE_PRESSED 1
#define KEY_STATE_RELEASED 0



void move_piece_up(int y); //transformar pra int e ver limites do ecra (retangulos)
void move_piece_down(int y);

#endif

