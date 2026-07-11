#include <stdio.h>
#include <stdlib.h>

#include "ADC.h"
#include "io.h"
#include "stats.h"


int main(void){
    FILE *data_file = fopen("adc_sensor_log.bin", "rb");
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

    //Moves the file reading to start of the ADC records, from header to the first record
    fseek(data_file, sizeof(File_header), SEEK_SET);

    ADCSample *samples = load_records(data_file, header.Record_count);
    if (samples == NULL) {
        printf("Failed to load ADC records\n");
        fclose(data_file);
        return 0;
    }
    printf("ADC records loaded successfully\n");

    //Raw value to voltage function
    voltage_conversion(samples, header.Record_count);

    //
    Channel_stats stats;
    for (int channel = 0; channel < header.Channel_count; channel++)
    {
        Compute_channel_stats(samples, header.Record_count, channel, &stats);

        printf("\nChannel %u\n", channel);
        printf("Mean voltage:       %f\n", stats.mean_voltage);
        printf("Minimum voltage:    %f\n", stats.minimum);
        printf("Maximum voltage:    %f\n", stats.maximum);
        printf("RMS voltage:        %f\n", stats.rms);
        printf("Standard deviation: %f\n", stats.standard_deviation);
    }

    fclose(data_file);
    free(samples);
    return 1;
}