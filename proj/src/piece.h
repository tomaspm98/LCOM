#ifndef __PIECE_H
#define __PIECE_H

#include <lcom/lcf.h>
#include <stdint.h>
#include "images/piece.xpm"
#include "entity.h"

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

int move_piece1_up(); //transformar pra int e ver limites do ecra (retangulos)
int move_piece1_down();
int move_piece2_up();
int move_piece2_down();
int draw_piece_1();
int draw_piece_2();

#endif

