#include "video.h"
#include <machine/int86.h>
#include <lcom/lab5.h>
#include <lcom/lcf.h>

int (read_mode)(vbe_mode_info_t *buffer, uint16_t mode){
  reg86_t r;
  memset(&r, 0, sizeof(r));	/* zero the structure */
  
  r.intno = 0x10;
  r.ax = 0x4F01; // VBE call, function 01 -- VBE mode info
  r.es = PB2BASE((int) &buffer);
  r.di = PB2OFF((int) &buffer);
  r.cx = mode;

  if( sys_int86(&r) != CALL_SUCCESS ) {
    printf("read_mode: sys_int86() failed \n");
    return 1;
  }

  return 0;
}

int (change_mode) (uint16_t mode) {
  reg86_t r;
  memset(&r, 0, sizeof(r));	/* zero the structure */

  r.intno = 0x10;
  r.ax = AH_DEFAULT<<8 | MODE_SET; // VBE call, function 02 -- set VBE mode
  r.bx = 1<<14 | mode; 

  if( sys_int86(&r) != CALL_SUCCESS ) {
    printf("change_mode: sys_int86() failed \n");
    return 1;
  }

  return 0;
}
