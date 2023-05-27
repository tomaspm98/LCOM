#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>

#include "keyboard/i8042.h"

int mouse_subscribe_int(uint8_t *bit_no);
int mouse_unsubscribe_int();
void delay();

int mouse_read();
int mouse_write(uint8_t cmd, uint8_t port);
int mouse_command(uint8_t cmd);
int mouse_discard();
int mouse_packet_process(uint8_t* data, struct packet* pp);













#endif  