#include "rtc.h"

int(rtc_write_addr)(uint8_t addr) {
  return sys_outb(RTC_ADDR_REG, addr);
}

int(rtc_read_data)(uint8_t *data) {
  return util_sys_inb(RTC_DATA_REG, data);
}

int(rtc_write_data)(uint8_t data) {
  return sys_outb(RTC_DATA_REG, data);
}

int(rtc_read_time)() {

  uint8_t reg;
  rtc_write_addr(RTC_REG_B);
  rtc_read_data(&reg);

  reg |= RTC_DM;

  rtc_write_addr(RTC_REG_B);
  rtc_write_data(reg);

  rtc_write_addr(RTC_REG_A);
  rtc_read_data(&reg);

  while (!reg & RTC_UIP) {
    rtc_write_addr(RTC_REG_A);
    rtc_read_data(&reg);
  }

  tickdelay(micros_to_ticks(WAIT));

  uint8_t time[6] = {0, 0, 0, 0, 0, 0};
  uint8_t regs[6] = {RTC_MONTH_DAY, RTC_MONTH, RTC_YEAR, RTC_HOURS, RTC_MINS, RTC_SECS};

  for (int i = 0; i < 6; i++) {
    rtc_write_addr(regs[i]);
    rtc_read_data(&time[i]);
  }

  printf("%02d/%02d/%02d - %02d:%02d:%02d\n", time[0], time[1], time[2], time[3], time[4], time[5]);
  return 0;
}
