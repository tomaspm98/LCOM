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

/// @brief Initiate the video card with the requested mode
/// @param submode VBE mode to initalize the grpahics
/// @return 0 if success, 1 if no success
int (set_graphic_mode)(uint16_t submode);

/// @brief 
/// @param mode 
/// @return 
void* (vg_init)(uint16_t mode);

/// @brief Defines the color of a pixel in the position x,y
/// @param x position x
/// @param y position y
/// @param color color of the pixel
/// @return 0 if success, 1 if no success
int (vg_drawpixel)(uint16_t x, uint16_t y, uint32_t color);

/// @brief Draws a rectangle with the requested width and height
/// @param x position x of the top left corner
/// @param y position y of the top left corner
/// @param width width of the rectangle
/// @param height height of the rectangle
/// @param color color of the rectangle
/// @return 0 if success, 1 if no success
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/// @brief Draws an horizontal line
/// @param x position x of the start of the line
/// @param y position y of the start of the line
/// @param len length of the line
/// @param color color of the line
/// @return 0 if success, 1 if no success
int (vg_drawline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/// @brief Displays the image we want by copying from image buffer to the main buffer
void displayImage();

/// @brief Sets the buffer with color white (0) and frees its memory
void freeImBuffer();

/// @brief Allocates memory to the draw buffer
void allocateDrawBuffer();

/// @brief Displays something we want by copying it from draw buffer to the main buffer
void copyDrawingToBuffer();

/// @brief Sets the buffer with color white (0)
void clearDrawBuffer();

/// @brief Free the memory of the draw buffer
void freeDrawBuffer();

/// @brief Allocates memory to the image buffer
void allocateImgBuffer();
