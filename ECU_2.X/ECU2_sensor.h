#ifndef ECU2_SENSOR_H
#define	ECU2_SENSOR_H

#include <stdint.h>

#define SPEED_ADC_CHANNEL 0x04

char* gear[] = {"GN", "G1", "G2", "G3", "G4", "G5", "GR", "_C"};

uint16_t get_speed();
uint8_t process_gear();

#endif	/* ECU1_SENSOR_H */

