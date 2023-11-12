#ifndef Clock_included
#define Clock_included

void configureClocks();
void enableWDTInterrupts();
void timerAUpmode();

unsigned char gert_srtest();
void set_srtest(), or_srtest(), and_srtest();

#endif // included
