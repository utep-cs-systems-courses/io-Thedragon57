#include <msp430.h>
#include "buzzer.h"
#include "StateMachine.h"
#include "switch.h"
#include "light.h"



int main(void) {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  P2DIR &= ~(BIT0 | BIT1 | BIT2| BIT3);//set the negation to have the direction of the button to 0
  P2OUT |= (BIT0 | BIT1 | BIT2 | BIT3);//sets the out dirction to 1
  P2REN |= (BIT0 | BIT1 | BIT2 | BIT3);//enables the pull resitors for ports 0-3
  P2IE |= (BIT0 | BIT1 | BIT2 | BIT3);//enable interupt
  P2IES |= (BIT0 | BIT1 | BIT2 | BIT3);//enable interupt edge select
  P2IFG &= ~(BIT0 | BIT1 | BIT2 | BIT3);//sets the interupt flag to 0
  timerAUpmode();
  P2DIR = BIT6;		/* enable output to speaker (P2.6) */
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  enable_lights();

  __bis_SR_register((LPM0_bits | GIE)); //LPM 4 disables watchdog timer and LMP 0 disables the cpu
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

void __interrupt_vec(WDT_VECTOR) WDT(){
  static char blink_count = 0;
  if (++blink_count == (rate/2) && blinking == 1) {
    light_toggle();
    blink_count = 0;
  }
}
