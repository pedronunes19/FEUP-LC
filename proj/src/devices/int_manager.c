#include "int_manager.h"

int (init)() {

  uint8_t timer_bit_no, kbd_bit_no, mouse_bit_no;

  timer_subscribe_int(&timer_bit_no);
  kbd_subscribe_int(&kbd_bit_no);
  mouse_subscribe_int(&mouse_bit_no);
  _mouse_enable_data_reporting();

  uint32_t timer_irq_set = BIT(timer_bit_no);
  uint32_t kbd_irq_set = BIT(kbd_bit_no);
  uint32_t mouse_irq_set = BIT(mouse_bit_no);

  message msg;
  int ipc_status;

  while (scan_code[kbd_i] != ESC_BREAK) {

    int r;
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != OK) {
      printf("driver_receive failed with: %d", r);
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {

        case HARDWARE: {

          if (msg.m_notify.interrupts & mouse_irq_set) {

            mouse_ih();
            if (mouse_ready) {

              mouse_ready = false;
              handle_mouse_event(&pp);

            }

          } else if (msg.m_notify.interrupts & kbd_irq_set) {
						 
						kbc_ih();
            
						if (scan_code[kbd_i] == TWO_BYTE_SC) {
							kbd_i++;
							continue;
						}

						kbd_i = 0;
            handle_kbd_event(&scan_code);

					} else if (msg.m_notify.interrupts & timer_irq_set) {

							timer_int_handler();
							
              if (timer_counter % 2 == 0) {
                handle_timer_event();
							}

					}	

          break;
        }

        default: break;
      }
    }
  }

	timer_unsubscribe_int();
	kbd_unsubscribe_int();
  mouse_unsubscribe_int();
  mouse_disable_data_reporting();

  return 0;
}
