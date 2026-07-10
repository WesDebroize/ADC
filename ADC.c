//
// Created by wesde on 29/06/2026.
//
//Converting raw_voltage to voltage
//voltage = (raw_value / 4095.0) * 3.3; // Use 4095.0 -- integer 4095 causes division to zero

#include "ADC.h"

#include <stdint.h>

#define VREF 3.3

//Raw_value to voltage conversion
void voltage_conversion(ADCSample *sample, uint32_t Record_count) {
    for (uint32_t i = 0; i < Record_count; i++) {
        sample->voltage = (sample->raw_value/ 4095.0) * VREF;
        sample++;
    }
}

