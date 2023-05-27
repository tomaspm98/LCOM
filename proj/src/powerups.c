#include "powerups.h"

int powerup_x;
int powerup_y;
//bool powerup = false;
bool no_pos = false;
bool catched_left;
bool catched_right;
extern int ball_x;
extern int ball_y;
extern int ball_var_y;
extern int ball_var_x;

int draw_powerup(){
    if (!no_pos){
        powerup_x = rand() % 528 + 130;
        powerup_y = rand() % 501 + 35;
        no_pos = true;
    }

    if (draw_xpm((xpm_map_t) powerup_xpm, powerup_x,powerup_y)) return 1;

    catched_right = false;  
    catched_left = false;  
    //powerup = true; 

    return 0;
}

int catch_powerup(){
    if (ball_var_x>0){  
        if ((ball_x+22>=powerup_x) && (ball_x<=powerup_x+30) && (ball_y+22>=powerup_y) && (ball_y<=powerup_y+30)){
            catched_left = true;
        }
    }
    else if (ball_var_x<0){
        if ((ball_x+22>=powerup_x) && (ball_x<=powerup_x+30) && (ball_y+22>=powerup_y) && (ball_y<=powerup_y+30)){
            catched_right = true;
        }
    }

    return 0;
}
