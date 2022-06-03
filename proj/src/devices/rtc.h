#include <lcom/lcf.h>
#include <stdint.h>

#include "rtc_defines.h"

int (rtc_write_addr) (uint8_t addr);
int (rtc_read_data) (uint8_t* data);
int (rtc_write_data) (uint8_t data);
int (rtc_read_time) ();
