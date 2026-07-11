//
// Created by wesde on 03/07/2026.
//
#include "stats.h"
#include <math.h>

void Compute_channel_stats(ADCSample *samples, uint32_t record_count, uint8_t channel_id, Channel_stats *stats) {
    ADCSample *sample = samples;

    int i;
    double voltage_total = 0.0;
    double squared_voltage_total = 0.0;
    double sqrt_diff_total = 0.0;
    uint32_t channel_count = 0;

    for (i = 0; i < record_count; i++) {
        if (sample->channel_id == channel_id) {

            voltage_total += sample->voltage;

            squared_voltage_total += sample->voltage * sample->voltage;

            //Starts min and max at the first voltage recordings for each channel
            if (channel_count == 0) {
                stats->minimum = sample->voltage;
                stats->maximum = sample->voltage;
            }
            else {
                //Min voltage
                if (sample->voltage < stats->minimum) {
                    stats->minimum = sample->voltage;
                }
                //Max voltage
                if (sample->voltage > stats->maximum) {
                    stats->maximum = sample->voltage;
                }
            }
            channel_count++;
        }
        sample++;
    }

    //Mean voltage
    stats->mean_voltage = voltage_total / channel_count;

    //RMS voltage
    stats->rms = sqrt(squared_voltage_total / channel_count);

    sample = samples;

    //Standard deviation - used a separate loop as mean voltage is needed
    for (i = 0; i < record_count; i++) {
        if (sample->channel_id == channel_id) {

            double diff = sample->voltage - stats->mean_voltage;

            sqrt_diff_total += diff * diff;

        }
        sample++;
    }

    //Standard deviation of voltage
    stats->standard_deviation = sqrt(sqrt_diff_total / channel_count);
}
