//
// Created by wesde on 29/06/2026.
//

#ifndef ADC_ADC_H
#define ADC_ADC_H
#include <stdint.h> //used for setting valuable memory sizes with uint_t


//Defining ADCSample struct
typedef struct __attribute__((packed)) {
    float timestamp;            //4 bytes   Seconds from start
    uint8_t channel_id;         //1 byte    ch no. = 0,1,2,3
    uint16_t raw_value;         //2 bytes   rng = 0-4095 (12-bit)
    uint16_t temperature;       //2 bytes   in tenths of degree C
    uint8_t status_flags;       //1 byte    0 = fault, 1 = OOR
    uint32_t sequence_number;   //4 bytes   Increments each record
    uint8_t reserved[2];        //2 bytes   Read + discard
} ADCSample_data;               //16 bytes total

#endif //ADC_ADC_H
