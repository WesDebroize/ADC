//
// Created by wesde on 29/06/2026.
//

#ifndef ADC_IO_H
#define ADC_IO_H

#include <stdio.h>
#include <stdint.h> //used for setting valuable memory sizes with uint_t
//Defining Header struct
typedef struct __attribute__((packed)){
    uint32_t magic;             //4 bytes   0xADC1BEEF — validate this first
    uint16_t version;           //2 bytes   Always 1
    uint16_t channel_count;     //2 bytes   Always 4
    uint32_t record_count;      //4 bytes   Use for malloc - always 4000
    uint32_t sample_rate_hz;    //4 bytes   Always 1000Hz
    uint8_t reserved[8];        //8 bytes   Read + Discard
} io_header;                       //24 bytes total
#endif //ADC_IO_H
