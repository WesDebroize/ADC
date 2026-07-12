//
// Created by wesde on 29/06/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "ADC.h"

//Read and Validate the header
int header_checker(const char filename[], File_header *header) {
    FILE *data_file = fopen(filename, "rb");    //rb - read in binary
    if (data_file == NULL) {
        printf("File couldnt open %s\n", filename); //Returns NULL if file couldnt be opened
        return 0;
    }
    /*
     Reads one 24-byte header (size of io_header) from the data_file and stores it into the
     io_header structure pointed to by header

     Didnt use &header as that would be the address of the pointer, not the header struct
     */
    if (fread(header, sizeof(File_header), 1, data_file) != 1) {  //checks that one complete io_header was read from the file
        printf("Couldnt read File_header\n");
        fclose(data_file);
        return 0;
    }
    //Checking magic number is 0xADC1BEEF
    if (header->Magic_number!= MAGIC_NUMBER) {
        printf("Expected 0x%08X, instead got 0x%08X\n",MAGIC_NUMBER,header->Magic_number); //%08X converts the integer to hexidecimal to 8 digits
        fclose(data_file);
        return 0;
    }
    //Validating record count
    fseek(data_file, 0, SEEK_END);

    long file_size = ftell(data_file);
    printf("File size is %ld\n", file_size);
    long record_count_size = file_size - sizeof(File_header);// 64024 - 24
    long real_record_count = record_count_size / sizeof(ADCBinaryRecords); // 64000/16

    if (real_record_count != (long)header->Record_count) {
        printf("Expected %u records, instead got %ld\n",header->Record_count,real_record_count);
        fclose(data_file);
        return 0;
    }

    //The file is opened, it could read the header, magic number is correct, record count is validated
    fclose(data_file);
    printf("File_header read successfully, magic number is 0x%08X, record count is %ld\n",header->Magic_number, real_record_count);
    return 1;
}


//Allocate memory (malloc) and load records

ADCSample *load_records(FILE *data_file, uint32_t record_count) {

    //Size of *samples = size of one ADCSample
    ADCSample *samples = malloc(record_count * sizeof(*samples));

    if (samples == NULL) {
        printf("Couldnt allocate memory for record_count\n");
        return NULL;
    }

    //Temporary struct used to read one 16 byte record from the binary file
    ADCBinaryRecords binary_record;
    //Pointer to ADCsample
    ADCSample *sample = samples;


    for (uint32_t i = 0; i < record_count; i++) {
        if (fread(&binary_record, sizeof(binary_record), 1, data_file) != 1) {
            //Reads one 16 byte record from the binary file into binary_record

            printf("Couldnt read binary_record\n");
            free(samples); //freeing memory before exit
            return NULL;
        }

        //Copying info from ADCBinaryRecords struct to the ADCSample struct
        sample->timestamp = binary_record.timestamp;
        sample->channel_id = binary_record.channel_id;
        sample->raw_value = binary_record.raw_value;
        sample->temperature = binary_record.temperature;
        sample->status_flags = binary_record.status_flags;
        sample->sequence_number = binary_record.sequence_number;

        sample++;

    }
    return samples;
}