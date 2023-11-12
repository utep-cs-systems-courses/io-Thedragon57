#include <msp430.h>
#include "Library.h"
#include "light.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;

  or_srtest(0x18);		/* CPU off, GIE on */
}
