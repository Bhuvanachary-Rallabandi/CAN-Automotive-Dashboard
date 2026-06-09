#ifndef ECU1_SENSOR_H
#define	ECU1_SENSOR_H

#include <stdint.h>

#define RPM_ADC_CHANNEL 0x04

#define LED_OFF 0
#define LED_ON 1

#define RIGHT_IND_ON() (PORTB = PORTB | 0xC0)
#define RIGHT_IND_OFF() (PORTB = PORTB & ~0xC0)
#define LEFT_IND_ON() (PORTB = PORTB | 0x03)
#define LEFT_IND_OFF() (PORTB = PORTB & ~0x03)

typedef enum {
    e_ind_off,
    e_ind_left,
    e_ind_right,
    e_ind_hazard
} IndicatorStatus;

uint16_t get_rpm();
IndicatorStatus process_indicator();

#endif	/* ECU1_SENSOR_H */

