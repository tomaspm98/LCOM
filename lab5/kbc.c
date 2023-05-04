#include <lcom/lcf.h>
#include <lcom/timer.h>
#include "i8042.h"

#include <stdint.h>
#include "kbc.h"
#include "i8254.h"

int (read_KBC_status)(uint8_t* status){
    if (util_sys_inb(KBC_STATUS_REG, status)) return 1;
    return 0;
}

int (read_KBC_output)(uint8_t port, uint8_t *output){
    int attempts=10;
    uint8_t status;

    while(attempts){
        if (read_KBC_status(&status)){
            printf("Error: Status not available!\n");
            return 1;
        }
        
        if ((status & FULL_OUT_BUFFER)!=0){
            if (util_sys_inb(port, output)){
                printf("Error: Error reading data\n");
                return 1;
            }
        if (status & PARITY_ERROR){
            printf("Error: Parity error\n");
            return 1;
        }
        if (status & TIMEOUT_ERROR){
            printf("Error: Timeout error\n");
            return 1;
        }
        return 0;
    }
        tickdelay(micros_to_ticks(20000));
        attempts--;
    }
    return 1;
}

int (write_KBC_command)(uint8_t port, uint8_t commandByte){
    int attempts=10; //fazer uint8_t se tiver mal
    uint8_t status;

    while(attempts){
        if (read_KBC_status(&status)) {
            printf("Error: Status not available!\n");
            return 1;
    }
        if (status & FULL_IN_BUFFER){
            printf("Error: Input buffer full!\n");
            return 1;
        }
        else {
            if (sys_outb(port, commandByte)){
                printf("Error: Can't write!\n");
                return 1;
            }
            return 0;
        }

    tickdelay(micros_to_ticks(20000));
    attempts--;
 }
    return 1;
}

int kbc_restore() {
    uint8_t commandWord;

  // Leitura da configuração atual
  if (write_KBC_command(0x64, 0x20) != 0)
    return 1;  // notificar o i8042 da leitura
    
  if (read_KBC_output(0x60, &commandWord) != 0)
    return 1;  // ler a configuração

  // Activar o bit das interrupções
  commandWord = commandWord | BIT(0);

  // Escrita da nova configuração
  if (write_KBC_command(0x64, 0x60) != 0)
    return 1;  // notificar o i8042 da escrita
    
  if (write_KBC_command(0x60, commandWord) != 0)
    return 1;  // escrever a configuração
    
  return 0;
}


