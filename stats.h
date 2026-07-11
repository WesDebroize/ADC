//
// Created by wesde on 29/06/2026.
//

#ifndef ADC_STATS_H
#define ADC_STATS_H
#include "ADC.h"

typedef struct {
    double mean_voltage;
    double rms;
    double minimum;
    double maximum;
    double standard_deviation;
}Channel_stats;

void Compute_channel_stats(ADCSample *sample, uint32_t record_count, uint8_t channel_id, Channel_stats *stats);

#endif //ADC_STATS_H
