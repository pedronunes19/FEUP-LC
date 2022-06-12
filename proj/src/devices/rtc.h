#include <lcom/lcf.h>
#include <stdint.h>

#include "rtc_defines.h"

typedef struct {
  uint16_t day;
  uint16_t month;
  uint16_t year;
} Date;

int (rtc_write_addr) (uint8_t addr);
int (rtc_read_data) (uint8_t* data);
int (rtc_write_data) (uint8_t data);
Date (rtc_read_time) ();
