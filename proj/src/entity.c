#include "entity.h"
#include "graphics/video_gr.h"
#include <lcom/lcf.h>


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Entity *create_sprite(xpm_map_t sprite) {
    Entity *sp = (Entity *) malloc ( sizeof(Entity));
    xpm_image_t img;
    if( sp == NULL )
        return NULL;
    sp->colors = (uint32_t *) xpm_load(sprite, XPM_8_8_8_8, &img);
    sp->height = img.height;
    sp->width = img.width;
    if( sp->colors == NULL ) {
        free(sp);
        return NULL;
    }

    return sp;
}

void destroy_sprite(Entity *sp) {
    if( sp == NULL )
        return;
    if( sp ->colors)
        free(sp->colors);
    free(sp);
    sp = NULL; 

}

int draw_sprite(Entity *sprite, int x, int y){
    for (int i=0;i<sprite->height;i++){
        for (int j=0;j<sprite->width;j++){
            if (vg_draw_pixel(x+j,y+i,sprite->colors[i*sprite->width + j])) return 1;
        }
    }
    return 0;
}

int draw_xpm(xpm_map_t xpm, int x, int y){
    xpm_image_t pic;
    uint32_t* colors = (uint32_t *) xpm_load(xpm, XPM_8_8_8_8, &pic);
    for (int i=0;i<pic.height;i++){
        for (int j=0;j<pic.width;j++){
            if (vg_draw_pixel(x+j,y+i,colors[i*pic.width + j])) return 1;
        }
    }
    return 0;
}





