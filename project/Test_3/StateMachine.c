#include <msp430.h>
#include "StateMachine.h"
#include "switch.h"
#include "light.h"


int state = 2;
int rate = 0;
int blink_count = 0;




void The_State_Machine(){
    switch(state){
        case 1:
            rate = 0;
            state = 2;
            break;
        case 2:
            rate = 50;
            state = 3;
            break;
        case 3:
            rate = 500;
            state = 4;
            break;
        case 4:
            rate = 5000;
            state = 1;
            break;
        default:
            rate = 0;
            state = 2;
            break;
    }
}

void state_change(int new_state){
    state = new_state;
    The_State_Machine();
}
