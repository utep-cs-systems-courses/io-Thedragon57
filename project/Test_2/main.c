#include <msp430.h>
#include "Library.h"
#include "light.h"
#include "switch.h"

void main(void)
{
  configureClocks();
  switch_init();
  led_init();

  or_srtest(0x18);  // CPU off, GIE on
}
