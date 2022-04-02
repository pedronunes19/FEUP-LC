#include <lcom/lcf.h>
#include <stdint.h>

#include "i8042.h"

#define PARITY_ERR   1
#define TIME_OUT_ERR 2
#define IBF_FULL     3

static int hook_id = 0;

int (keyboard_subscribe_int) (uint8_t* bit_no);
int (keyboard_unsubscribe_int) ();
int (check_status) (uint8_t st);