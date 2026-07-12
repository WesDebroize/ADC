//
// Created by wesde on 29/06/2026.
//
//Converting raw_voltage to voltage
//voltage = (raw_value / 4095.0) * 3.3; // Use 4095.0 -- integer 4095 causes division to zero

#include "ADC.h"
#include "stats.h"
#include <stdint.h>

#define VREF 3.3

//Raw_value to voltage conversion
void voltage_conversion(ADCSample *sample, uint32_t Record_count) {
    for (uint32_t i = 0; i < Record_count; i++) {
        sample->voltage = (sample->raw_value/ 4095.0) * VREF;
        sample++;
    }
}
void Compute_channel_stats(ADCSample *samples, uint32_t record_count, uint8_t channel_id, Channel_stats *stats) {
    stats->mean_voltage = Compute_mean_voltage(samples, record_count, channel_id);
    stats->rms = Compute_RMS_voltage(samples, record_count, channel_id);
    stats->minimum = Compute_minimum_voltage(samples, record_count, channel_id);
    stats->maximum = Compute_maximum_voltage(samples, record_count, channel_id);
    stats->standard_deviation = Compute_standard_deviation(samples, record_count, channel_id, stats->mean_voltage);
}
void Detect_channel_faults(ADCSample *samples, uint32_t record_count, uint8_t channel_id, Fault_counts *faults) {

    ADCSample *sample = samples;

    faults->overvoltage_count = 0;
    faults->undervoltage_count = 0;
    faults->sensor_fault_count = 0;
    faults->total_fault_count = 0;

    for (uint32_t i = 0; i < record_count; i++) {
        if (sample->channel_id == channel_id) {
            int faults_detected = 0;

            //Overvoltage fault
            if (sample->voltage > 3.0) {
                faults->overvoltage_count++;
                faults_detected = 1;
            }

            //Undervoltage fault
            if (sample->voltage < 0.3) {
                faults->undervoltage_count++;
                faults_detected = 1;
            }

            //Status flag bit 0 set (sensor fault)
            if ((sample->status_flags & 0x01) != 0) {
                faults->sensor_fault_count++;
                faults_detected = 1;
            }

            //Adding fault to total
            if (faults_detected == 1) {
                faults->total_fault_count++;
            }
        }
        sample++;
    }
}

