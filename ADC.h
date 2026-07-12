//
// Created by wesde on 29/06/2026.
//

#ifndef ADC_ADC_H
#define ADC_ADC_H
#include <stdint.h> //Used to create fixed memory sized integer types


//Defining ADCBinaryRecords struct
typedef struct __attribute__((packed)) { //Packed tells the compiler to not insert padding, otherwise the struct will be the wrong size
    float timestamp;            //4 bytes   Seconds from start
    uint8_t channel_id;         //1 byte    Ch NO. = 0,1,2,3
    uint16_t raw_value;         //2 bytes   Range = 0-4095 (12-bit)
    int16_t temperature;        //2 bytes   In tenths of degree C
    uint8_t status_flags;       //1 byte    0 = fault, 1 = OOR, rest reserved
    uint32_t sequence_number;   //4 bytes   Increments each record
    uint8_t reserved[2];        //2 bytes   Read + discard
} ADCBinaryRecords;                    //16 bytes total

//Defining new struct to store results for program
typedef struct {
    float timestamp;
    uint8_t channel_id;
    uint16_t raw_value;
    double voltage;
    int16_t temperature;
    uint8_t status_flags;
    uint32_t sequence_number;
}ADCSample;


void voltage_conversion(ADCSample *sample, uint32_t record_count);

typedef struct {
    double mean_voltage;
    double rms;
    double minimum;
    double maximum;
    double standard_deviation;
}Channel_stats;

void Compute_channel_stats(ADCSample *sample, uint32_t record_count, uint8_t channel_id, Channel_stats *stats);

typedef struct {
    uint32_t overvoltage_count;
    uint32_t undervoltage_count;
    uint32_t sensor_fault_count;
    uint32_t total_fault_count;
} Fault_counts;

void Detect_channel_faults(ADCSample *samples, uint32_t record_count, uint8_t channel_id, Fault_counts *faults);

typedef struct {
    uint32_t last_sequence;
    uint32_t current_sequence;
    uint32_t missing_count;
} Sequence_issue;

uint32_t Check_sampling_integrity(ADCSample *samples,uint32_t record_count,Sequence_issue *issues);

#endif //ADC_ADC_H
