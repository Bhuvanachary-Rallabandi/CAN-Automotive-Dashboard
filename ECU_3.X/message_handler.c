#include <xc.h>
#include "clcd.h"
#include "timer.h"
#include "can.h"
#include "msg_id.h"
#include "message_handler.h"

void handle_speed_data(uint8_t *data, uint8_t len)
{    
    uint16_t speed = (data[0] << 8) | data[1];

    clcd_putch((speed / 100) + '0', LINE2(0));
    clcd_putch(((speed / 10) % 10) + '0', LINE2(1));
    clcd_putch((speed % 10) + '0', LINE2(2));
}

void handle_gear_data(uint8_t *data, uint8_t len)
{
   uint8_t i = *data;
   clcd_print(gear[i], LINE2(4));
}

void handle_rpm_data(uint8_t *data, uint8_t len)
{
    uint16_t rpm = (data[0] << 8) | data[1];

    clcd_putch((rpm / 1000) + '0', LINE2(7));
    clcd_putch(((rpm / 100) % 10) + '0', LINE2(8));
    clcd_putch(((rpm / 10) % 10) + '0', LINE2(9));
    clcd_putch((rpm % 10) + '0', LINE2(10));
}

void handle_indicator_data(uint8_t *data, uint8_t len)
{
    status = *data;
    if(status == e_ind_off || timer_flag == 0)
    {
        RIGHT_IND_OFF();
        LEFT_IND_OFF();
        clcd_print("    ", LINE2(12));
    }
    else if(status == e_ind_left)
    {
        RIGHT_IND_OFF();
        LEFT_IND_ON();
        clcd_print("<-  ", LINE2(12));
    }
    else if(status == e_ind_right)
    {
        RIGHT_IND_ON();
        LEFT_IND_OFF();
        clcd_print("  ->", LINE2(12));
    }
    else if(status == e_ind_hazard)
    {
        RIGHT_IND_ON();
        LEFT_IND_ON();
        clcd_print("<-->", LINE2(12));
    }
}

void process_canbus_data()
{
    uint16_t msg_id;
    uint8_t data[8];
    uint8_t len;
    can_receive(&msg_id, data, &len);
    if(msg_id == SPEED_MSG_ID)
    {
        handle_speed_data(data, len);
    }
    else if(msg_id == GEAR_MSG_ID)
    {
        handle_gear_data(data, len);
    }
    else if(msg_id == RPM_MSG_ID)
    {
        handle_rpm_data(data, len);
    }
    else if(msg_id == INDICATOR_MSG_ID)
    {
        handle_indicator_data(data, len);
    }
}