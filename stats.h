//
// Created by wesde on 29/06/2026.
//

#ifndef ADC_STATS_H
#define ADC_STATS_H
#include "ADC.h"

double Compute_mean_voltage(ADCSample *samples, uint32_t record_count, uint8_t channel_id);

double Compute_RMS_voltage(ADCSample *samples, uint32_t record_count, uint8_t channel_id);

double Compute_minimum_voltage(ADCSample *samples, uint32_t record_count, uint8_t channel_id);

double Compute_maximum_voltage(ADCSample *samples, uint32_t record_count, uint8_t channel_id);

double Compute_standard_deviation(ADCSample *samples, uint32_t record_count, uint8_t channel_id, double mean_voltage);





#endif //ADC_STATS_H
