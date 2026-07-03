//
// Created by wesde on 29/06/2026.
//

#ifndef ADC_IO_H
#define ADC_IO_H

#include "ADC.h"
#include <stdio.h>
#include <stdint.h> //used for setting valuable memory sizes with uint_t
#define MAGIC_NUMBER 0xADC1BEEF
//Defining Header struct
typedef struct __attribute__((packed)){
    uint32_t magic;             //4 bytes   0xADC1BEEF — validate this first
    uint16_t version;           //2 bytes   Always 1
    uint16_t channel_count;     //2 bytes   Always 4
    uint32_t record_count;      //4 bytes   Use for malloc - always 4000
    uint32_t sample_rate_hz;    //4 bytes   Always 1000Hz
    uint8_t reserved[8];        //8 bytes   Read + Discard
} io_header;                    //24 bytes total


//Function declarations

int header_checker(const char filename[], io_header *header);

ADCSample *load_records(FILE *data_file, uint32_t record_count);

#endif //ADC_IO_H
