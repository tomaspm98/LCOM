#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_

#include <minix/sysutil.h>
#include "i8042.h"
#include <lcom/lcf.h>

#endif /* _LCOM_KBC_H_ */

int (kbc_read_stat)(uint8_t* status);

int (kbc_read_out)(uint8_t port, uint8_t *output);

int (kbc_write_cmd)(uint8_t port, uint8_t command_byte);

int (kbc_restore) ();
