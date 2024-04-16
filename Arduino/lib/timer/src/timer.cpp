#include "timer.h"

void timer_interrupt_init() {
  cli(); // Stoppe alle interrupts
  /*
    Først nullstiller vi kontrollregisteret for å sikre at vi starter med alt
    Dette gjøA prescaler in a hardware timer module is a digital circuit that is
    used to divide the clock signal’s frequency by a configurable number to
    bring down the timer clock rate so it takes longer to reach the overflow
    (maximum count number).r vi ved å skrive 0 (nullstille) til TCCR1A og TCCR1B
  */
  TCCR1A = 0x00;
  TCCR1B = 0x00;

  TCCR1B = (1 << CS12) |
           (1 << CS10); // Sette prescaler til 1024 -> 16MHz / 1024 = 15625Hz

  // Slå på 'clear timer on compare match' (CTC) mode, dette vil nullstille
  // timeren når den når verdien satt i OCR1A
  TCCR1B |= (1 << WGM12);

  TIMSK1 = (1 << OCIE1A); // Aktivere 'Compare Match A' interrupt

  OCR1A = 31250; // Set OCIE1A to 1 so we enable compare match A

  sei(); // Aktivere alle interrupts
}
