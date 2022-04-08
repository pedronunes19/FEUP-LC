#include "keyboard.h"

static int hook_id = 0;
uint8_t scan_code[] = {0, 0};
int scan_code_size = 0;
uint8_t ih_flag = 0;
uint8_t end_flag = 0;
bool handling_two_bytes = false;

int(kbd_subscribe_int)(uint8_t *bit_no) {

  *bit_no = hook_id;
  return sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int(kbd_unsubscribe_int)() {

  return sys_irqrmpolicy(&hook_id);
}

void(kbd_ih)() {

  uint8_t output;
  util_sys_inb(OUT_BUF, &output);

  uint8_t st;
  util_sys_inb(STATUS_REG, &st);

  if (check_status(st) == OK) {

    scan_code_size++;
    scan_code[0] = output;

    if (scan_code[0] == TWO_BYTE_SC) {
      handling_two_bytes = true;
    }
    else if (handling_two_bytes) {
      scan_code[0] = TWO_BYTE_SC;
      scan_code[1] = output;
      handling_two_bytes = false;
    }

    if (!handling_two_bytes) {
      if (output & IS_BREAK)
        ih_flag = IS_BREAKCODE;
      else
        ih_flag = IS_MAKECODE;
    }

    else
      ih_flag = IH_STATUS_ERROR;
  }
}

void(kbd_reset_globals)() {
  scan_code_size = 0;
  end_flag = scan_code[0];
  scan_code[0] = 0;
  scan_code[1] = 0;
}

int(check_status)(uint8_t st) {

  if (st & PARITY) {
    return PARITY_ERR;
  }

  if (st & TIME_OUT) {
    return TIME_OUT_ERR;
  }

  /* might cause issues with the lab, since we won't be writing to the input buffer
  if (st & IBF) {
      return IBF_FULL;
  }
  */

  return OK;
}
