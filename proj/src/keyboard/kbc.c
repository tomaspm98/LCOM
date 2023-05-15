#include <lcom/lcf.h>
#include <lcom/timer.h>
#include "i8042.h"

#include <stdint.h>
#include "kbc.h"
#include "timer/i8254.h"

int (read_KBC_status)(uint8_t* status){
    if (util_sys_inb(KBC_STATUS_REG, status)) return 1;
    return 0;
}

int (read_KBC_output)(uint8_t port, uint8_t *output){ //ver se podes ler e dps ler e verificar erros
    uint8_t status, attempts=10;
    while(attempts){
        if (read_KBC_status(&status)){ 
            return 1;
        }

        if ((status & FULL_OUT_BUFFER)==0){
            return 1; 
        }
        else {
            if (status & PARITY_ERROR){
                return 1;
            }

            if (status & TIMEOUT_ERROR){
                return 1;
            }
            return 0;
        }
        tickdelay(micros_to_ticks(20000));
        attempts--;
    }
    return 1;
}

int (write_KBC_command)(uint8_t port, uint8_t commandByte){ //verifiar se podes escrever e dps escreves
    uint8_t attempts=10;
    uint8_t status;

    while(attempts){
        if (read_KBC_status(&status)){
            return 1;
        }

        if (status & FULL_IN_BUFFER){
            return 1;
        } else {
            if (sys_outb(port,commandByte)){
                return 1;
            }
            return 0;
        }
        tickdelay(micros_to_ticks(20000));
        attempts--;
    }
    return 1;
}

int kbc_restore() { //notificar i i8042 tanto da leitura como da escrita e dps de cada uma fazer efetivamente isso
  uint8_t controlWord;

  if (write_KBC_command(KBC_STATUS_REG, 0x20)){
    return 1;
  }

  if (read_KBC_output(KBC_OUT_CMD, &controlWord)){
    return 1;
  }

  controlWord = controlWord | BIT(0);

  if (write_KBC_command(KBC_STATUS_REG, 0x60)){
    return 1;
  }

  if (write_KBC_command(KBC_WRITE_CMD, controlWord)){
    return 1;
  }

  return 0;


  return 0;
}


