#include <avr/interrupt.h>
#include <stdint.h>

#include "hw.h"
#include "tick.h"

static uint8_t switch_state = OFF;
static uint32_t switch_time = 0;

static uint8_t poll_switch(void)
{
  const uint32_t now = millis();

  if (switch_pressed())
  {
    if ((switch_state == OFF) && ((now - switch_time) > DEBOUNCE_MS))
    {
      switch_state = ON;
      switch_time = now;
      return 1;
    }
    return 0;
  }
  else
  {
    if ((switch_state == ON) && ((now - switch_time) > DEBOUNCE_MS))
    {
      switch_state = OFF;

      if ((now - switch_time) > HOLD_THRESHOLD_MS)
      {
        switch_time = now;
        return 1;
      }

      switch_time = now;
    }
    return 0;
  }
}

int main(void)
{
  io_init();
  tick_init_1ms();
  sei();

  while (1)
  {
    if (poll_switch())
    {
      relay_toggle();
      led_toggle();
    }
  }
}
