#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8042.h"
#include "kbc.h"

#endif /* _LCOM_KEYBOARD_H_ */

int (keyboard_subscribe_intrpt)(uint8_t *bit_no);

int (keyboard_unsubscribe_intrpt)();

void (kbc_ih)();



