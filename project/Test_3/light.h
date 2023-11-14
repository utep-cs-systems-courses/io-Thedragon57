#ifndef Library_included
#define Library_included

#define LED_RED BIT6               // P1.6
#define LED_GREEN BIT0             // P1.0
#define LEDS (BIT0 | BIT6)

void enable_lights();

void light_toggle();


#endif // included
