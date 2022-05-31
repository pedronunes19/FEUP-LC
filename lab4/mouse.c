#include "mouse.h"

int kbd_hook_id = 1;
int mouse_hook_id = 12;

struct packet pp;

int (mouse_subscribe_int)(uint8_t *bit_no) {
  *bit_no = mouse_hook_id;
  return sys_irqsetpolicy(KBD_AUX_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int (kdb_subscribe_int)(uint8_t *bit_no) {
  *bit_no = kbd_hook_id;
  return sys_irqsetpolicy(KBD_AUX_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id);
}

int (mouse_unsubscribe_int)() {
  return sys_irqrmpolicy(&mouse_hook_id);
}

int (kbd_unsubscribe_int)() {
  return sys_irqrmpolicy(&kbd_hook_id);
}

int (mouse_enable_data_reporting)() {
  
}

void (mouse_ih)() {
  uint8_t output;
  util_sys_inb(OUT_BUF, &output);
}