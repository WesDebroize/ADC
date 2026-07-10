//
// Created by wesde on 29/06/2026.
//
//Converting raw_voltage to voltage
//voltage = (raw_value / 4095.0) * 3.3; // Use 4095.0 -- integer 4095 causes division to zero

#include "ADC.h"

#include <stdint.h>

#define VREF 3.3


//void voltage_conversion(ADC_data *sample, uint32_t Record_count) {}

