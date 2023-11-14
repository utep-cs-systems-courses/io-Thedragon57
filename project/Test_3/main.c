#include <msp430.h>
#include "Library.h"
#include "light.h"
#include "switch.h"
#include "StateMachine.h"

int main(void) {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  enable_lights();
  Port2_interupt();

  or_srtest(0x18);			/* CPU off, GIE on */
}

void __interrupt_vec(WDT_VECTOR) watchdog(){
  if(++blink_count == (rate/2)){
    light_toggle();
    blink_count = 0;
  }
}
