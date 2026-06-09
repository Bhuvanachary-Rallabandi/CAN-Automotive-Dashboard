/*
 * File:   main.c
 * Author: BhuvanaChary.R
 *
 * Created on 14 April, 2026, 11:22 PM
 */



#include <xc.h>
#include "can.h"
#include "dkp.h"
#include "adc.h"
#include "msg_id.h"
#include "ECU1_sensor.h"

void init_config(void) {
    init_dkp();
    init_can();
    init_adc();
}

uint8_t flag;

void main(void) {
    init_config();
    while (1) {
        uint16_t rpm = get_rpm();
        can_transmit(RPM_MSG_ID, &rpm, sizeof (rpm));
        for (int delay = 50; delay--;);
        
        IndicatorStatus cur_ind_status = process_indicator();
        can_transmit(INDICATOR_MSG_ID, &cur_ind_status, sizeof (cur_ind_status));
        for (int delay = 100; delay--;);           
    }
    return;
}

uint16_t get_rpm() {
    return ((read_adc(RPM_ADC_CHANNEL) / 10.23) * 60);
}

IndicatorStatus process_indicator() {
    char key = read_dkp();

    if (key == SW1)
        flag = 1;
    else if (key == SW2)
        flag = 2;
    else if (key == SW3)
        flag = 3;
    else if (key == SW4)
        flag = 4;

    if (flag == 1)
        return e_ind_left;
    else if (flag == 2)
        return e_ind_right;
    else if (flag == 3)
        return e_ind_hazard;
    else if (flag == 4)
        return e_ind_off;
    
    
    return e_ind_off;
}