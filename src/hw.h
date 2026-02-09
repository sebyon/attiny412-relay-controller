#pragma once

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// ---- Behaviour constants ----
#define SETTLE_MS 5
#define DEBOUNCE_MS 75
#define HOLD_THRESHOLD_MS 300

#define ON 1
#define OFF 0

// ---- Pin assignment (ATtiny412) ----
// TODO: Check PIN Assignments

#define SW_bm PIN0_bm        // PA0 Switch
#define LED_bm PIN1_bm       // PA1 LED
#define RELAY_RST_bm PIN2_bm // PA2 Relay RESET
#define RELAY_SET_bm PIN3_bm // PA3 Relay SET

static inline uint8_t switch_pressed(void)
{
    // active-low with pull-up
    return (VPORTA.IN & SW_bm) == 0;
}

void io_init(void);

void led_toggle(void);

void relay_on(void);
void relay_off(void);
void relay_toggle(void);

uint8_t relay_state(void);
