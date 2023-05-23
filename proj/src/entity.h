#ifndef ENTITY_H
#define ENTITY_H

#include <lcom/lcf.h>
#include <stdint.h>

typedef struct {
    int width, height; // dimensions
    uint32_t *colors; // the pixmap
} Entity;

void destroy_sprite (Entity *sp);
Entity *create_sprite (xpm_map_t sprite);
int drawSprite(Entity *sprite, int x, int y);
int draw_xpm(xpm_map_t xpm, int x, int y);

#endif /* ENTITY_H */
