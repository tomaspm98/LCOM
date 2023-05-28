#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_

#include <minix/sysutil.h>
#include "i8042.h"
#include <lcom/lcf.h>

#endif /* _LCOM_KBC_H_ */

/// @brief Read the KBC status
/// @param status KBC status
/// @return 0 if success, 1 if no success
int (read_KBC_status)(uint8_t* status);

/// @brief Read the output 
/// @param port port
/// @param output output to be read
/// @return 0 if success, 1 if no success
int (read_KBC_output)(uint8_t port, uint8_t *output);

/// @brief Writes command in port
/// @param port port
/// @param commandByte command to be written
/// @return  0 if success, 1 if no success
int (write_KBC_command)(uint8_t port, uint8_t commandByte);

/// @brief Returns to the default KBC configuration
/// @return 0 if success, 1 if no success
int (kbc_restore) ();
