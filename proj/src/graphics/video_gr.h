#ifndef _LCOM_VIDEO_GR_H_
#define _LCOM_VIDEO_GR_H_

#include <minix/sysutil.h>
#include "keyboard/i8042.h"
#include <lcom/lcf.h>

#endif /* _LCOM_KEYBOARD_H_ */

#define WHITE 0xFFFFFF
extern int h_res;
extern int v_res;
extern uint8_t* vram;
extern uint8_t* backbuffer;

int (set_graphic_mode)(uint16_t submode);
void* (vg_init)(uint16_t mode);
int (vg_drawpixel)(uint16_t x, uint16_t y, uint32_t color);
uint32_t (R)(uint32_t first);
uint32_t (G)(uint32_t first);
uint32_t (B)(uint32_t first);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
int (vg_drawline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
void displayImage();
void freeImBuffer();
void allocateDrawBuffer();
void copyDrawingToBuffer();
void clearDrawBuffer();
void freeDrawBuffer();
void allocateImgBuffer();
