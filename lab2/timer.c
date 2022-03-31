#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint32_t rb_comm = TIMER_RB_CMD | BIT(5) | BIT(timer + 1);
  sys_outb(TIMER_CTRL, rb_comm);

  uint8_t conf = timer_get_conf(timer, &conf);
  conf &= 0x0f;

  uint32_t ctrl_word = conf | BIT(5) | BIT (4);

  switch (timer) {
    case 0: ctrl_word |= TIMER_SEL0; break;
    case 1: ctrl_word |= TIMER_SEL1; break;
    case 2: ctrl_word |= TIMER_SEL2; break;
    default: return -1;
  }

  sys_outb(TIMER_CTRL, ctrl_word);

  uint32_t new_clk = TIMER_FREQ/freq;

  uint8_t lsb = 0, msb = 0;

  util_get_LSB((uint16_t) new_clk, &lsb);
  util_get_MSB((uint16_t) new_clk, &msb);
  /*
  uint8_t lsb = (uint8_t) new_clk;
  new_clk = new_clk >> 8;
  uint8_t msb = (uint8_t) new_clk;*/

  switch (timer) {
    case 0: sys_outb(TIMER_0, lsb); sys_outb(TIMER_0, msb); break;
    case 1: sys_outb(TIMER_1, lsb); sys_outb(TIMER_1, msb); break;
    case 2: sys_outb(TIMER_2, lsb); sys_outb(TIMER_2, msb); break;
    default: return -1;
  }

  return 0;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  switch(timer) {

    case 0: return util_sys_inb(TIMER_0, st);

    case 1: return util_sys_inb(TIMER_1, st);

    case 2: return util_sys_inb(TIMER_2, st);

    default: return 1;
  };
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val val;

  switch (field) {
    case tsf_all:
      val.byte = st;
      return timer_print_config(timer, field, val);
    case tsf_initial:
      val.in_mode = ((st & (BIT(5) | BIT(6))) >> 4);
      return timer_print_config(timer, field, val);
    case tsf_mode:
      val.count_mode = ((st & (BIT(1) | BIT(2) | BIT(3))) >> 1);
      return timer_print_config(timer, field, val);
    case tsf_base:
      val.bcd = (st & BIT(0));
      return timer_print_config(timer, field, val);
  }
}
