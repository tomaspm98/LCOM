#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t *pixels;
} Picture;

typedef struct {
    int x;
    int y;
    Picture *imgFrames;
    unsigned int frameCount;
} Entity;

Entity* createEntity(int posX, int posY);
int addFrame(Entity* entity, char* file);
int renderEntity(Entity* entity, unsigned int idx, int posX, int posY);
int addFrameXPM(Entity* entity, char* file);

#endif /* ENTITY_H */
