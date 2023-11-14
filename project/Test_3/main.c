#include <msp430.h>
#include "Library.h"
#include "light.h"

static state = 2;
static blink_rate = 0;
static blink_count = 0;

int main(void) {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  enable_lights();
  Port2_interupts();

  or_srtest(0x18);			/* CPU off, GIE on */
}

void __interrupt_vec(WDT_VECTOR) watchdog(){
  if(blink_count == (blink_rate/2)){
    light_toggle();
    blink_count = 0;
  }
}
