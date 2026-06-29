//
// Created by wesde on 29/06/2026.
//

#ifndef ADC_ADC_H
#define ADC_ADC_H
#include <stdint.h> //used for setting valuable memory sizes with uint_t
//Defining Header struct
typedef struct {
    uint32_t magic;             //4 bytes   0xADC1BEEF — validate this first
    uint16_t version;           //2 bytes   Always 1
    uint16_t channel_count;     //2 bytes   Always 4
    uint32_t record_count;      //4 bytes   Use for malloc - always 4000
    uint32_t sample_rate_hz;    //4 bytes   Always 1000Hz
    uint8_t reserved[8];        //8 bytes   Read + Discard
} header;                       //24 bytes total

//Defining ADCSample struct
typedef struct {
    float timestamp;            //4 bytes   Seconds from start
    uint8_t channel_id;         //1 byte    ch no. = 0,1,2,3
    uint16_t raw_value;         //2 bytes   rng = 0-4095 (12-bit)
    uint16_t temperature;       //2 bytes   in tenths of degree C
    uint8_t status_flags;       //1 byte    0 = fault, 1 = OOR
    uint32_t sequence_number;   //4 bytes   Increments each record
    uint8_t reserved[2];        //2 bytes   Read + discard
} ADCsample_data;               //16 bytes total
#endif //ADC_ADC_H
