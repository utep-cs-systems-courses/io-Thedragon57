#include <msp430.h>
#include "StateMachine.h"
#include "switch.h"
#include "light.h"
#include "buzzer.h"

int state = 2;
int toggle_led = 0;
short rate = 0x100;
char blinking = 0;
short frz = 0;


void The_State_Machine(){
  switch(state){
    case 1:
      blinking = 1;
      if (frz < 1900){
        frz += 100;
        buzzer_set_period(frz);
      }
      if(rate > 0x10)
      rate = rate >> 1;
      state = 2;
      break;
    case 2:
      lights_off();
      buzzer_set_period(0);
      blinking = 0;
      state = 3;
      break;
    case 3:
      lights_on();
      blinking = 0;
      state = 4;
      break;
    case 4:
      blinking = 1;
      if (frz > 100){
        frz -= 100;
        buzzer_set_period(frz);
      }
      if(rate < 0x400);
      rate = rate << 1;
      state = 1;
      break;
    default:
      buzzer_set_period(0);
      state = 2;
      break;
  }
}

void state_change(int new_state){
    state = new_state;
    The_State_Machine();
}
