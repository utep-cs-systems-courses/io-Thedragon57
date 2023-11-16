#include <msp430.h>
//#include "Library.h"


int main(void) {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  P2DIR &= ~(BIT0 | BIT1 | BIT2| BIT3);//set the negation to have the direction of the button to 0
  P2OUT |= (BIT0 | BIT1 | BIT2 | BIT3);//sets the out dirction to 1
  P2REN |= (BIT0 | BIT1 | BIT2 | BIT3);//enables the pull resitors for ports 0-3
  P2IE |= (BIT0 | BIT1 | BIT2 | BIT3);//enable interupt
  P2IES |= (BIT0 | BIT1 | BIT2 | BIT3);//enable interupt edge select
  P2IFG &= ~(BIT0 | BIT1 | BIT2 | BIT3);//sets the interupt flag to 0
  enable_lights();
    //Port2_interupt();

  __bis_SR_register((LPM4_bits | GIE));
}


void configureClocks(){
  WDTCTL = WDTPW + WDTHOLD;//Disable Watchdog Timer
  BCSCTL1 = CALBC1_16MHZ;  // Set DCO to 16 Mhz
  DCOCTL = CALDCO_16MHZ;

  BCSCTL2 &= ~(SELS);     // SMCLK source = DCO
  BCSCTL2 |= DIVS_3;      // SMCLK = DCO / 8
}


// enable watchdog timer periodic interrupt
// period = SMCLOCK/32k
void enableWDTInterrupts()
{
  WDTCTL = WDTPW |	   // passwd req'd.  Otherwise device resets
    WDTTMSEL |		     // watchdog interval mode
    WDTCNTCL |		     // clear watchdog count
    1;			     // divide SMCLK by 8192
  IE1 |= WDTIE;		   // Enable watchdog interval timer interrupt
}


void timerAUpmode()
{
  TA0CCR0 = 0;
  TA0CCR1 = 0;
  TA0CCTL1 = OUTMOD_3;		/* Toggle p1.6 when timer=count1 */

  // Timer A control:
  //  Timer clock source 2: system clock (SMCLK)
  //  Mode Control 1: continuously 0...CCR0
  TACTL = TASSEL_2 + MC_1;
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){ //telling the computer that when an intrupt happens to use this funtion
  if(P2IFG & BIT0){
    //lights_off();
    state_change(1);
    P2IFG &= ~(BIT0);
  }
  if(P2IFG & BIT1){
    state_change(2);
    //lights_on();
    P2IFG &= ~(BIT1);
  }

  if(P2IFG & BIT2){
    state_change(3);
    P2IFG &= ~(BIT2);
  }

  if(P2IFG & BIT3){
    state_change(4);
    P2IFG &= ~(BIT3);
  }
}

void enable_lights(){
    P1DIR |= (BIT0 | BIT6);
    P1OUT |= (BIT0 | BIT6);
}

void light_toggle(){
    P1OUT ^= (BIT0 | BIT6);
}

void lights_on(){
    P1OUT |= (BIT0 | BIT6);
}

void lights_off(){
    P1OUT &= ~(BIT0 | BIT6);
}

int state = 2;
int toggle_led = 0;





void The_State_Machine(){
  switch(state){
    case 1:
      DimQuater();
      state = 2;
      break;
    case 2:
      lights_off();
      state = 3;
      break;
    case 3:
      lights_on();
      state = 4;
      break;
    case 4:

      state = 1;
      break;
    default:

      state = 2;
      break;
  }
}

void state_change(int new_state){
    state = new_state;
    The_State_Machine();
}

void DimQuater(){
  switch (toggle_led){
    case 0:
      light_toggle();
      toggle_led++;
      break;
    case 1:
      light_toggle();
      toggle_led++;
      break;
    case 2:
      toggle_led++;
      break;
    case 3:
      light_toggle();
      toggle_led = 0;
      break;
    default:
      break;
  }
}
