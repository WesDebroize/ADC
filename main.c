#include <stdio.h>
#include <stdlib.h>

#include "ADC.h"
#include "io.h"

int main(void){
    FILE *data_file = fopen("adc_sensor_log.bin", "rb");
    /*test to see why file cant be opened
    if (data_file == NULL) {
        perror("couldnt open file");
        return 0;
    }
    */
   // printf("Size of ADCSample: %zu bytes\n", sizeof(io_header)); - used to check size of both headers
    File_header header; //Variable to store the 24-byte file header
    //Calls header_checker function from io.c
   if (header_checker("adc_sensor_log.bin", &header) == 0) {
       printf("Header validation failed\n");
       fclose(data_file);
       return 0;
   }
    //printing header to check all info and size is correct
    printf("Magic no.: %x\n", header.Magic_number);
    printf("Version %u\n", header.File_version);
    printf("Channels: %u\n", header.Channel_count);
    printf("Record count: %u\n", header.Record_count);
    printf("Sample rate: %uhz\n", header.Sample_rate);
    printf("Size of header: %zu bytes\n", sizeof(header));



    ADCSample *samples = load_records(data_file, header.Record_count);
    if (samples == NULL) {
        printf("Failed to load ADC records\n");
        fclose(data_file);
        return 0;
    }
    printf("ADC records loaded successfully\n");
    fclose(data_file);
    free(samples);
    return 1;
}