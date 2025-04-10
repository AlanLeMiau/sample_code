

#include <avr/io.h>
#include <avr/interrupt.h>

#include "HAL_TIMER1.h"

#define F_CPU 16000000UL

void HAL_TIMER1_init() {
    cli(); // Disable global interrupts

    TCCR1A = 0; // Set entire TCCR1A register to 0
    TCCR1B = 0; // Set entire TCCR1B register to 0

    // Set CTC mode (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);

    
    // Calculate and set OCR1A for 1-second interval
    // Formula: OCR1A = (F_CPU / (Prescaler * Frequency)) - 1
    // Set prescaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    OCR1A = (16000000 / (1024 * 1)) - 1;
    
    // Calculate and set OCR1A for 4-millisecond interval
    // For 4ms: Frequency = 1 / 0.004 = 250 Hz
    // OCR1A = (F_CPU / (64 * 250)) - 1;

    // Enable Timer1 compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    sei(); // Enable global interrupts

}

ISR(TIMER1_COMPA_vect) {
    ISR_TIMER1();
}