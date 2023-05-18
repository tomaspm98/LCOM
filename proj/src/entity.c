#include "entity.h"
#include "graphics/video_gr.h"


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Entity* createEntity(int posX, int posY){
    Entity* newObj = (Entity*)malloc(sizeof(Entity));
    
    newObj->imgFrames = NULL;
    newObj->frameCount = 0;
    newObj->x = posX;
    newObj->y = posY;

    return newObj;
}

int addFrame(Entity* entity, char* file){
    FILE* fileHandler;

    if((fileHandler = fopen(file, "r")) == NULL ) return 1;

    if(entity->imgFrames != NULL){
        entity->imgFrames = realloc(entity->imgFrames, sizeof(Picture) * (entity->frameCount+1));
    } else {
        entity->imgFrames = (Picture*)malloc(sizeof(Picture) * (entity->frameCount+1));
    }

    Picture* newPic = &(entity->imgFrames[entity->frameCount]);

    if(fread(&(newPic->width), sizeof(uint16_t), 1, fileHandler) == 0) return 1;
    if(fread(&(newPic->height), sizeof(uint16_t), 1, fileHandler) == 0) return 1;

    newPic->pixels = (uint8_t*)malloc(newPic->width * newPic->height);
    if(fread(newPic->pixels, sizeof(uint8_t), newPic->width * newPic->height, fileHandler) 
        < newPic->width * newPic->height) return 1;
    
    if(fclose(fileHandler) != 0) return 1;

    entity->frameCount++;

    return 0;
}

int renderEntity(Entity* entity, unsigned int idx, int posX, int posY){
    int render_x = posX + entity->x;
    int render_y = posY + entity->y;

    uint8_t* buffer_ptr = backbuffer + render_x + render_y*h_res;

    for(unsigned int i=0; i<entity->imgFrames[idx].height; i++){
        for(unsigned int j=0; j<entity->imgFrames[idx].width; j++){
            uint8_t pixel = entity->imgFrames[idx].pixels[j + i*entity->imgFrames[idx].width];
            // Entry 0 is transparency.
            int pixel_x = j+render_x;
            int pixel_y = i+render_y;
            if(pixel && (pixel_x >= 0 && pixel_x < (int)h_res && pixel_y >= 0 && pixel_y < (int)v_res)){
                buffer_ptr[j] = pixel;
            }
        }
        buffer_ptr += h_res;
    }

    return 0;
}

#include <string.h>

int addFrameXPM(Entity* entity, char* file){
    printf("Entering addFrameXPM\n");

    FILE* fileHandler;

    if((fileHandler = fopen(file, "r")) == NULL ){ 
        printf("Failed to open file\n");
        return 1;
    }

    if(entity->imgFrames != NULL){
        entity->imgFrames = realloc(entity->imgFrames, sizeof(Picture) * (entity->frameCount+1));
    } else {
        entity->imgFrames = (Picture*)malloc(sizeof(Picture) * (entity->frameCount+1));
    }

    Picture* newPic = &(entity->imgFrames[entity->frameCount]);

    char buffer[256];
    uint16_t colors;
    
    printf("OK");
    // read header
    uint16_t chars;
    char header[256];
    if(fgets(header, sizeof(header), fileHandler) == NULL) return 1;
    printf("OK");
    sscanf(header, "%hu %hu %hu %hu", &(newPic->width), &(newPic->height), &colors, &chars);
    
    printf("Read header: %hu, %hu, %hu\n", newPic->width, newPic->height, colors);
    
    // skip color table
    for (int i = 0; i < colors; i++) {
        if (fgets(buffer, sizeof(buffer), fileHandler) == NULL) return 1;
    }

    newPic->pixels = (uint8_t*)malloc(newPic->width * newPic->height);
    if (newPic->pixels == NULL) {
        printf("Failed to allocate memory for pixels\n");
        return 1;
    }

    printf("Allocated memory for pixels\n");

    for(uint16_t i = 0; i < newPic->height; i++) {
        for(uint16_t j = 0; j < newPic->width; j++) {
            char pixel;
            if (fscanf(fileHandler, " %c", &pixel) != 1) {
                printf("Failed to read pixel at position (%hu, %hu)\n", i, j);
                return 1;
            }
            newPic->pixels[j + i*newPic->width] = (uint8_t)pixel;
        }

        // Skip newline
        if (fscanf(fileHandler, "%*[\n]") < 0) {
            printf("Failed to skip newline after line %hu\n", i);
            return 1;
        }
    }

    if(fclose(fileHandler) != 0) return 1;

    entity->frameCount++;

    printf("EXITING\n");

    return 0;
}



