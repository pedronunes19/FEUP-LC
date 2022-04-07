#ifndef _KBD_H_
#define _KBD_H_

#include <lcom/lcf.h>
#include <stdint.h>

#include "i8042.h"

#define PARITY_ERR   1
#define TIME_OUT_ERR 2
#define IBF_FULL     3

int (kbd_subscribe_int) (uint8_t* bit_no);
int (kbd_unsubscribe_int) ();
int (kbd_int_handler) ();
int (check_status) (uint8_t st);

#endif /*_KBD_H_*/
