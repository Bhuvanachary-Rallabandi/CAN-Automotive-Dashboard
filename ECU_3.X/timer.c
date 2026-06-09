#include <xc.h>
//initialize TIMER0
void init_timer0(void)
{
    TMR0ON = 1;
    T08BIT = 1;
    T0CS = 0;
    PSA = 1;
    TMR0 = 6;
    TMR0IE = 1;
    TMR0IF = 0;
}