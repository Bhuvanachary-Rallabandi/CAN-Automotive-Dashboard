/*
 * File:   main.c
 * Author: BhuvanaChary .R
 *
 * Created on 14 April, 2026, 11:31 PM
 */



#include <xc.h>
#include "can.h"
#include "dkp.h"
#include "adc.h"
#include "msg_id.h"
#include "ECU2_sensor.h"

void init_config(void) {
    init_dkp();
    init_can();
    init_adc();
}
int collision_flag, index;

void main(void) {
    init_config();
    int speed = 0;
    while (1) {
        uint16_t speed = get_speed();
        can_transmit(SPEED_MSG_ID, &speed, sizeof (speed));
        for (int delay = 150; delay--;);
        
        uint8_t cur_gear_status = process_gear();
        can_transmit(GEAR_MSG_ID, &cur_gear_status, sizeof (cur_gear_status));
        for (int delay = 200; delay--;);
    }
    return;
}

uint16_t get_speed() {
    return read_adc(SPEED_ADC_CHANNEL) / 10.23;
}

uint8_t process_gear() {
    char key = read_dkp();
    if (key == SW1) {
        if (collision_flag)
            index = 0;
        else if (++index >= 6)
            index = 6;
        collision_flag = 0;
    } else if (key == SW2) {
        if (collision_flag)
            index = 0;
        else if (--index <= 0)
            index = 0;
        collision_flag = 0;
    } else if (key == SW3) {
        collision_flag = 1;
        index = 7;
    }
    return index;
}