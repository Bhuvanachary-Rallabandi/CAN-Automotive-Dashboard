#include <xc.h>

extern char timer_flag;

//Interrupt Service Routine
void __interrupt() isr(void)
{
    static int count;
    //Check Timer0 overflow interrupt
    if(TMR0IF == 1)
    {
        TMR0IF = 0; //Clear Timer0 interrupt flag
        TMR0 = TMR0 + 8;
        //Check Timer0 count limit
        if(count++ == 10000)
        {
            timer_flag = !timer_flag;
            count = 0; //Reset Timer0 counter
        }
    }
}