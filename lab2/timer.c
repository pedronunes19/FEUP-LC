#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  switch(timer) {

    case 0: return util_sys_inb((int)TIMER_0, st);

    case 1: return util_sys_inb(TIMER_1, st);

    case 2: return util_sys_inb(TIMER_2, st);

    default: return 1;
  };
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val val;

  // TODO: Figure out how timer_print_config works :(
  switch (field) {
    case tsf_all:
      val.byte = st;
      return timer_print_config(timer, field, val);
    case tsf_initial:
      val.in_mode = ((st & 0x30) >> 4);
      return timer_print_config(timer, field, val);
    case tsf_mode:
      val.count_mode = ((st & 0x0E) >> 1);
      return timer_print_config(timer, field, val);
    case tsf_base:
      val.bcd = (st & 0x01);
      return timer_print_config(timer, field, val);
  }
}
