#include <msp430.h>
#include "StateMachines.h"
#include "light.h"

void The_State_Machine(){
    switch(State){
        case 1:
            blink_rate = 0;
            state = 2;
            break;
        case 2:
            blink_rate = 16;
            state = 3;
            break;
        case 3:
            blink_rate = 32;
            state = 4;
            break;
        case 4:
            blink_rate = 64;
            state = 1;
            break;
        default:
            blink_rate = 0;
            state = 2;
            break;
    }
}

void state_change(new_state){
    state = new_state;
    The_State_Machine();
}
