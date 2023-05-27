#include <lcom/lcf.h>

#include "piece.h"

int piece_1_x = 30;
int piece_1_y = 255;
int piece_2_x = 757;
int piece_2_y = 255;

void move_piece1_up(){
    piece_1_y-=20;
}

void move_piece1_down(){
    piece_1_y+=20;
}

void move_piece2_up(){
    piece_2_y-=20;
}

void move_piece2_down(){
    piece_2_y+=20;
}

int draw_piece_1(){
    if (draw_xpm((xpm_map_t) piece_xpm,piece_1_x,piece_1_y)) return 1; 
    return 0;
}

int draw_piece_2(){
    if (draw_xpm((xpm_map_t) piece_xpm,piece_2_x,piece_2_y)) return 1;
    return 0;
}
