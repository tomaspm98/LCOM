#include "ball.h"

#include <lcom/lcf.h>


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int ball_x = 390;
int ball_y = 290;
int ball_var_y;
int ball_var_x;
bool startBall = true;
int side_start=-1;
bool goal = false;
int goal_left = 0;
int goal_right=0;
extern int piece_1_x;
extern int piece_1_y;
extern int piece_2_x;
extern int piece_2_y;
bool not_random = false;

int start_ball(){
    if (goal){
        goal = false;
        ball_x = 390;
        ball_y = 290;
        ball_var_x = 0;
        ball_var_y = 0;
        tickdelay(100);
    }
    if (!not_random){
        srand(time(NULL));
        side_start = rand() % 2;
        not_random = true;
    }
         if (side_start==0){
                ball_var_x=-5;
         }
         else {
            if(side_start==1){
                ball_var_x=5;
                
         }
    }
    if ((ball_x==45 || ball_x==735) && ((ball_y+21>=piece_1_y && ball_y<=piece_1_y+89) || (ball_y+21>=piece_2_y && ball_y<=piece_2_y+89))){ 
        startBall = false;
    }

    return 0;
}

int collision_ball_piece1(){
    if (ball_x == 45){    
    int mid = piece_1_y + 46-11;
    int top1 = piece_1_y-11+36;
    int top2 = piece_1_y-11+26;
    int top3 = piece_1_y-11+16;
    int top4 = piece_1_y-11+6;
    int top5 = piece_1_y-15;
    int top6 = piece_1_y -21;
    int bot1 = piece_1_y-11+46;
    int bot2 = piece_1_y-11+56;
    int bot3 = piece_1_y-11+66;
    int bot4 = piece_1_y-11+76;
    int bot5 = piece_1_y-11+86;
    int bot6 = piece_1_y-11+96; 

    if (ball_y == mid){
        ball_var_y=0;
        ball_var_x=5;
    }
    else if (ball_y<mid && ball_y>=top1){
        ball_var_x=5;
        ball_var_y=-1; 
    }

    else if (ball_y<top1 && ball_y>=top2){
        ball_var_x=5;
        ball_var_y=-2; 
    }

    else if (ball_y<top2 && ball_y>=top3){
        ball_var_x=5;
        ball_var_y=-3; 
    }
    else if (ball_y<top3 && ball_y>=top4){
        ball_var_x=5;
        ball_var_y=-4;
    }
    else if (ball_y<top4 && ball_y>=top5){
        ball_var_x=5;
        ball_var_y=-5; 
    }
    else if (ball_y<top5 && ball_y>=top6){
        ball_var_x=5;
        ball_var_y=-6; 
    }
    else if (ball_y>mid && ball_y<=bot1){
        ball_var_x=5;
        ball_var_y=1; 
    }
    else if (ball_y>bot1 && ball_y<=bot2){
        ball_var_x=5;
        ball_var_y=2; 
    }
    else if (ball_y>bot2 && ball_y<=bot3){
        ball_var_x=5;
        ball_var_y=3; 
    }
    else if (ball_y>bot3 && ball_y<=bot4){
        ball_var_x=5;
        ball_var_y=4; 
    }
    else if (ball_y>bot4 && ball_y<=bot5){
        ball_var_x=5;
        ball_var_y=5; 
    }
    else if (ball_y>bot5 && ball_y<=bot6){
        ball_var_x=5;
        ball_var_y=6; 
    }    
   }

   return 0;
}

int collision_ball_piece2(){
    if (ball_x == 735){
    int mid = piece_2_y +46-11;
    int top1 = piece_2_y-11+36;
    int top2 = piece_2_y-11+26;
    int top3 = piece_2_y-11+16;
    int top4 = piece_2_y-11+6;
    int top5 = piece_2_y-15;
    int top6 = piece_2_y -21;
    int bot1 = piece_2_y-11+46;
    int bot2 = piece_2_y-11+56;
    int bot3 = piece_2_y-11+66;
    int bot4 = piece_2_y-11+76;
    int bot5 = piece_2_y-11+86;
    int bot6 = piece_2_y-11+96; 
    if (ball_y == mid){
        ball_var_y=0;
        ball_var_x=-5;
    }
    else if (ball_y<mid && ball_y>=top1){
        ball_var_x=-5;
        ball_var_y=-1; 
    }

    else if (ball_y<top1 && ball_y>=top2){
        ball_var_x=-5;
        ball_var_y=-2; 
    }

    else if (ball_y<top2 && ball_y>=top3){
        ball_var_x=-5;
        ball_var_y=-3; 
    }

    else if (ball_y<top3 && ball_y>=top4){
        ball_var_x=-5;
        ball_var_y=-4; 
    }
    else if (ball_y<top4 && ball_y>=top5){
        ball_var_x=-5;
        ball_var_y=-5; 
    }
    else if (ball_y<top5 && ball_y>=top6){
        ball_var_x=-5;
        ball_var_y=-6; 
    }
    else if (ball_y>mid && ball_y<=bot1){
        ball_var_x=-5;
        ball_var_y=1; 
    }
    else if (ball_y>bot1 && ball_y<=bot2){
        ball_var_x=-5;
        ball_var_y=2; 
    }
    else if (ball_y>bot2 && ball_y<=bot3){
        ball_var_x=-5;
        ball_var_y=3; 
    }
    else if (ball_y>bot3 && ball_y<=bot4){
        ball_var_x=-5;
        ball_var_y=4; 
    }
    else if (ball_y>bot4 && ball_y<=bot5){
        ball_var_x=-5;
        ball_var_y=5; 
    }
    else if (ball_y>bot5 && ball_y<=bot6){
        ball_var_x=-5;
        ball_var_y=6; 
    }    
   }
   if ((ball_y>=34 && ball_y<=40) || (ball_y >= 540 && ball_y<=546)){
    if(ball_var_x<0){
        ball_var_x = -5;
        ball_var_y = -ball_var_y;
    }
    else {
        ball_var_x = 5;
        ball_var_y = -ball_var_y;
    }
   }

   return 0;
}

int goal_left_piece(){
    goal = true;
    startBall = true;
    not_random = true;
    goal_left++;
    if (draw_xpm((xpm_map_t) letter_g_xpm,327,284)) return 1;
    if (draw_xpm((xpm_map_t) letter_o_xpm,365,284)) return 1;
    if (draw_xpm((xpm_map_t) letter_a_xpm,403,284)) return 1;
    if (draw_xpm((xpm_map_t) letter_l_xpm,441,284)) return 1;

    return 0;
}

int goal_right_piece(){
    goal = true;
    startBall = true;
    not_random = true;
    goal_right++;
    if (draw_xpm((xpm_map_t) letter_g_xpm,327,284)) return 1;
    if (draw_xpm((xpm_map_t) letter_o_xpm,365,284)) return 1;
    if (draw_xpm((xpm_map_t) letter_a_xpm,403,284)) return 1;
    if (draw_xpm((xpm_map_t) letter_l_xpm,441,284)) return 1;

    return 0;
}

int ball_pos_variation(){
    ball_x+=ball_var_x;
    ball_y+=ball_var_y;

    return 0; 
}
int ball_movement(){
   if (startBall){ 
    if (start_ball()) return 1;
   }

   collision_ball_piece1();

   collision_ball_piece2();

   if (ball_x == 0){
        goal_left_piece();
    }
    else if (ball_x == 770){
        goal_right_piece();
    }
   
   ball_pos_variation();

   return 0;
}

int draw_ball(){
    if (!goal){
        if (draw_xpm((xpm_map_t) ball_xpm,ball_x,ball_y)) return 1;
   }
   return 0;
}

int score(){
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

    return 0;

}
