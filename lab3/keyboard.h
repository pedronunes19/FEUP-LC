#ifndef _KBD_H_
#define _KBD_H_

#include <lcom/lcf.h>
#include <stdint.h>

#include "i8042.h"

#define PARITY_ERR   1
#define TIME_OUT_ERR 2
#define IBF_FULL     3

#define IS_BREAKCODE 1
#define IS_MAKECODE 2
#define IH_STATUS_ERROR 5

int (kbd_subscribe_int) (uint8_t* bit_no);
int (kbd_unsubscribe_int) ();
void (kbd_ih) ();
void (kbd_reset_globals) ();
int (check_status) (uint8_t st);

#endif /*_KBD_H_*/
