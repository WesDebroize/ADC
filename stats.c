//
// Created by wesde on 03/07/2026.
//
#include "stats.h"
#include <math.h>

double Compute_mean_voltage(ADCSample *samples, uint32_t record_count, uint8_t channel_id) {

    ADCSample *sample = samples;
    double voltage_total = 0.0;
    uint32_t channel_count = 0;

    for (uint32_t i = 0; i < record_count; i++) {
        if (sample->channel_id == channel_id) {
            voltage_total += sample->voltage;
            channel_count++;
        }
        sample++;
    }
    return voltage_total / channel_count;
}

double Compute_RMS_voltage(ADCSample *samples, uint32_t record_count, uint8_t channel_id) {

    ADCSample *sample = samples;
    double squared_voltage_total = 0.0;
    uint32_t channel_count = 0;

    for (uint32_t i = 0; i < record_count; i++) {
        if (sample->channel_id == channel_id) {
            squared_voltage_total += sample->voltage * sample->voltage;
            channel_count++;
        }
        sample++;
    }
    return sqrt(squared_voltage_total / channel_count);
}

double Compute_minimum_voltage(ADCSample *samples, uint32_t record_count, uint8_t channel_id) {

    ADCSample *sample = samples;
    double minimum;
    uint32_t channel_count = 0;

    for (int i = 0; i < record_count; i++) {
        if (sample->channel_id == channel_id) {
            if (channel_count == 0) {
                minimum = sample->voltage;
            }
            if (sample->voltage < minimum) {
                minimum = sample->voltage;
            }
            channel_count++;
        }
        sample++;
    }
    return minimum;
}

double Compute_maximum_voltage(ADCSample *samples, uint32_t record_count, uint8_t channel_id) {

    ADCSample *sample = samples;
    double maximum;
    uint32_t channel_count = 0;

    for (uint32_t i = 0; i < record_count; i++) {
        if (sample->channel_id == channel_id) {
            if (channel_count == 0) {
                maximum = sample->voltage;
            }
            if (sample->voltage > maximum) {
                maximum = sample->voltage;
            }
            channel_count++;
        }
        sample++;
    }
    return maximum;
}

double Compute_standard_deviation(ADCSample *samples, uint32_t record_count, uint8_t channel_id, double mean_voltage) {

    ADCSample *sample = samples;
    double square_diff_total = 0.0;
    uint32_t channel_count = 0;

    for (uint32_t i = 0; i < record_count; i++) {
        if (sample->channel_id == channel_id) {
            double diff = sample->voltage - mean_voltage;
            square_diff_total += diff * diff;
            channel_count++;
        }
        sample++;
    }
    return sqrt(square_diff_total / channel_count);
}