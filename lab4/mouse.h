#include "i8042_mouse.h"
#include <lcom/lcf.h>
#include <lcom/lab4.h>

#define DELAY_US 20000

extern int kbd_hook_id = 1;
extern int mouse_hook_id = 12;

extern struct packet pp;

int (mouse_subscribe_int) (uint8_t* bit_no);
int (kdb_subscribe_int)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();
int (kbd_unsubscribe_int)();
int (mouse_enable_data_reporting)();
void (mouse_ih)();
