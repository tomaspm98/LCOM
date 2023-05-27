#ifndef __BALL_H
#define __BALL_H

#include <lcom/lcf.h>
#include <stdint.h>
#include "images/letter_g.xpm"
#include "images/letter_o.xpm"
#include "images/letter_a.xpm"
#include "images/letter_l.xpm"
#include "images/number_zero.xpm"
#include "images/number_one.xpm"
#include "images/number_two.xpm"
#include "images/number_three.xpm"
#include "images/nada.xpm"

#include "piece.h"

int start_ball();
int collision_ball_piece1();
int ball_movement();
int draw_ball();
int goal_leftPiece();
int goal_rightPiece();
int score();

#endif


