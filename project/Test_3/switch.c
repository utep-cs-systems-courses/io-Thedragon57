#include <msp430.h>
#include "switch.h"
#include "light.h"

void Port2_buttons(){
  P2DIR &= ~(BIT0 | BIT1 | BIT2| BIT3);//set the negation to have the direction of the button to 0
  P2REN |= (BIT0 | BIT1 | BIT2 | BIT3);//enables the pull resitors for ports 0-3
  P2OUT |= (BIT0 | BIT1 | BIT2 | BIT3);//sets the out dirction to 1
  P2IE |= (BIT0 | BIT1 | BIT2 | BIT3);//enable interupt
  P2IES |= (BIT0 | BIT1 | BIT2 | BIT3);//enable interupt edge select
  P2IEG &= ~(BIT0 | BIT1 | BIT2 | BIT3);//sets the interupt flag to 0
}

void __interrupt_vec(PORT2_VECTOR) Port2_interupt(){ //telling the computer that when an intrupt happens to use this funtion
  if(P2IFG & BIT0){
    state_change(1);
  }
  if(P2IFG & BIT1){
    state_change(2);
  }

  if(P2IFG & BIT2){
    state_change(3);
  }

  if(P2IFG & BIT3){
    state_change(4);
  }
}
