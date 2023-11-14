#include <msp430.h>
#include "StateMachine.h"
#include "switch.h"
#include "light.h"


/*
void __interrupt_vec(WDT_VECTOR) watchdog(){
  if(++blink_count == (rate/2)){
    light_toggle();
    blink_count = 0;
  }
}
*/
