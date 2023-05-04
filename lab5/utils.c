#include <lcom/lcf.h>

#include <stdint.h>

int counter_KBC=0;

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  /* To be implemented by the students */
  if (lsb==NULL)
     return 1;
  *lsb= (uint8_t) val;
  return 0;   
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  /* To be implemented by the students */
  if (msb==NULL)
    return 1;
  *msb = (uint8_t) (val>>8);
  return 0;  
}

int (util_sys_inb)(int port, uint8_t *value) { //queres escrever em val faz se *val
  /* To be implemented by the students */      //qnd um argumento de uma funçao e com *, se a quisermos invocar usar esse argumento com &
  uint32_t aux;
  if (sys_inb(port, &aux)) return 1;
  #ifdef LAB3
  counter_KBC++;
  #endif

  *value=(uint8_t) aux;

  return 0;

}
