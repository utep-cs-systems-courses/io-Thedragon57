#ifndef StateMachine_included
#define StateMachine_included



extern int state;
extern int toggle_led;
extern short rate;
extern char blinking;
extern short frz;


void The_State_Machine();
void state_change(int);

#endif // included
