#include "tick.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

static volatile uint32_t g_ms = 0;

// 1 ms interrupt handler for TCB0
ISR(TCB0_INT_vect)
{
    g_ms++;
    TCB0.INTFLAGS = TCB_CAPT_bm; // clear interrupt flag
}

void tick_init_1ms(void)
{
    // 1 ms period using CLK_PER (no divider)
    // CCMP = F_CPU / 1000 - 1
    const uint16_t ccmp = (uint16_t)(F_CPU / 1000UL - 1UL);

    TCB0.CTRLA = 0;                  // disable while configuring
    TCB0.CTRLB = TCB_CNTMODE_INT_gc; // periodic interrupt mode
    TCB0.CCMP = ccmp;
    TCB0.CNT = 0;

    TCB0.INTCTRL = TCB_CAPT_bm; // enable interrupt
    TCB0.CTRLA = TCB_CLKSEL_CLKDIV1_gc | TCB_ENABLE_bm;
}

uint32_t millis(void)
{
    uint32_t v;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        v = g_ms;
    }
    return v;
}
