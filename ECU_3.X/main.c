/*
 * File:   main.c
 * Author: BhuvanaChary .R
 *
 * Created on 14 April, 2026, 11:36 PM
 */


#include <xc.h>
#include "clcd.h"
#include "can.h"
#include "timer.h"
#include "msg_id.h"
#include "message_handler.h"

void init_config(void)
{
    GIE = 1;
    PEIE = 1;
    init_timer0();
    init_can();
    init_clcd();
    TRISB = 0x3c;
    PORTB = 0;
}

volatile unsigned char status;
char timer_flag;

void main(void) {
    init_config();
    clcd_print("SP  GR RPM  IND ", LINE1(0));
    while(1)
    {
        process_canbus_data();
    }
    return;
}
