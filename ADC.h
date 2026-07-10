//
// Created by wesde on 29/06/2026.
//

#ifndef ADC_ADC_H
#define ADC_ADC_H
#include <stdint.h> //Used to create fixed memory sized integer types


//Defining ADCSample struct
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

#endif //ADC_ADC_H
