#include "hw.h"

static uint8_t g_relay_state = OFF;

uint8_t relay_state(void)
{
    return g_relay_state;
}

// The ATTiny412 has a single 8-bit port (PORTA) with 7 usable pins (PA0-PA6).
void io_init(void)
{
    // outputs
    PORTA.DIRSET = LED_bm | RELAY_SET_bm | RELAY_RST_bm;

    // input + pull-up on PA0
    PORTA.DIRCLR = SW_bm;
    PORTA.PIN0CTRL = PORT_PULLUPEN_bm;

    // start low
    PORTA.OUTCLR = LED_bm | RELAY_SET_bm | RELAY_RST_bm;

    relay_off();
}

void led_toggle(void)
{
    PORTA.OUTTGL = LED_bm;
}

void relay_on(void)
{
    PORTA.OUTSET = RELAY_SET_bm;
    PORTA.OUTCLR = RELAY_RST_bm;

    _delay_ms(SETTLE_MS);

    PORTA.OUTCLR = RELAY_SET_bm;
    g_relay_state = ON;
}

void relay_off(void)
{
    PORTA.OUTSET = RELAY_RST_bm;
    PORTA.OUTCLR = RELAY_SET_bm;

    _delay_ms(SETTLE_MS);

    PORTA.OUTCLR = RELAY_RST_bm;
    g_relay_state = OFF;
}

void relay_toggle(void)
{
    if (g_relay_state == OFF)
        relay_on();
    else
        relay_off();
}
