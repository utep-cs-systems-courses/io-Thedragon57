#include <msp430.h>
#include "light.h"
#include "switch.h"

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}

void led_update(){
  if(switch_state_changed) {
    if(switch_state_down) {
      P1OUT &= ~(LED_GREEN | LED_RED);
    } else {
      P1OUT |= (LED_GREEN | LED_RED);
    }
}
  switch_state_changed = 0;
}
