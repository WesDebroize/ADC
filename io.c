//
// Created by wesde on 29/06/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "ADC.h"

//Read and Validate the header
int header_checker(const char filename[], io_header *header) {
    FILE *data_file = fopen(filename, "rb");    //rb - read in binary
    if (data_file == NULL) {
        printf("File couldnt open %s\n", filename); //Returns NULL if file couldnt be opened
        return 0;
    }
    //Checking if io_header is the correct size
    if (sizeof(io_header) != 24) {
        printf("Header isnt 24 bytes, its instead %zu bytes\n", sizeof(io_header));
        fclose(data_file);
        return 0;
    }

    /*
     Reads one 24-byte header (size of io_header) from the data_file and stores it into the
     io_header structure pointed to by header

     Didnt use &header as that would be the address of the pointer, not the header struct
     */
    if (fread(header, sizeof(io_header), 1, data_file) != 1) {  //checks that one complete io_header was read from the file
        printf("Couldnt read io_header\n");
        fclose(data_file);
        return 0;
    }
    //Checking magic number is 0xADC1BEEF
    if (header->magic != MAGIC_NUMBER) {
        printf("Expected 0x%08X, instead got 0x%08X\n",MAGIC_NUMBER,header->magic); //%08X converts the integer to hexidecimal to 8 digits
        fclose(data_file);
        return 0;
    }
    //The file is opened, it's the correct size, it could read the header, magic number is correct
    fclose(data_file);
    printf("io_header read successfully, magic number is 0x%08X\n",header->magic);
    return 1;
}


//Allocate memory (malloc) and load records

uint32_t i;
ADCSample *samples;

ADCSample *load_records(FILE *data_file, uint32_t record_count) {
    samples = malloc(record_count * sizeof(ADCSample)); //4000 * 16 = 64000

    if (samples == NULL) {
        printf("Couldnt allocate memory for record_count\n");
        return NULL;
    }
    for (i = 0; i < record_count; i++) {
        if (fread(&samples[i], sizeof(ADCSample), 1, data_file) != 1) {
            /*Reads one line from the ADC file (the size of ADCSample is 16 bytes)
             *and stores it in samples[i]
             *
             *Should range from samples[0] to samples[3999] - 4000 total
             */
            printf("Couldnt read ADCSample\n");
            free(samples);
            return NULL;
        }
    }
    return samples;
}