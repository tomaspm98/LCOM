#include "menu.h"
#include "entity.h"
#include "graphics/video_gr.h"
#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Entity *game_title;
Entity *start_button;
Entity *quit_button;

int start_button_x;
int start_button_y;
int quit_button_x;
int quit_button_y;

void loadSprites() {
    game_title = create_sprite((xpm_map_t)game_name_xpm);
    start_button = create_sprite((xpm_map_t)startbutton_xpm);
    quit_button = create_sprite((xpm_map_t)quitbutton_xpm);

}

void destroySprites() {
    destroy_sprite(game_title);
    destroy_sprite(start_button);
    destroy_sprite(quit_button);

}

void displayMenu() {
    vg_clear_screen();

    drawSprite(game_title, 590, 390);
    start_button_x = 590 + (game_title->width / 2) - (start_button->width / 2);
    start_button_y = 390 + game_title->height + 50; // separar os 2 mas no mesmo y
    quit_button_x = start_button_x + start_button->width + 50;
    quit_button_y = start_button_y;
    drawSprite(start_button, start_button_x, start_button_y);
    drawSprite(quit_button, quit_button_x, quit_button_y);

    vg_update_screen();
}

void handleMouse() {
    struct packet pp;
    if (mouse_read_packet(&pp) != 0) {
        printf("Error: Failed to read mouse packet\n");
        return 1;
    }
    if (pp.lb) {

        if (pp.x >= start_button_x && pp.x < (start_button_x + start_button->width) &&
            pp.y >= start_button_y && pp.y < (start_button_y + start_button->height)) {
            inMenu = false;
        }

        if (pp.x >= quit_button_x && pp.x < (quit_button_x + quit_button->width) &&
            pp.y >= quit_button_y && pp.y < (quit_button_y + quit_button->height)) {
            exit(0); 
        }
    }
}
