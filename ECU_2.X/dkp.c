#include <xc.h>
//function for initialize digital keypads
void init_dkp(void)
{
    TRISC = TRISC | 0x0F;
}
//function for read which switch is pressed
char read_dkp()
{
    static int flag = 0;
    // Check for new key press
    if(flag == 0 && ((PORTC & 0x0F) != 0x0F))
    {
        flag = 1;
        // Return pressed switch value
        return PORTC & 0x0F;
    }
    // Check if all keys are released
    else if((PORTC & 0x0F) == 0x0F)
    {
        //reset flag to 0
        flag = 0;
    }
    return 0x0F;
}