#include <stdio.h>
#include <stdlib.h>

#include "ADC.h"
#include "io.h"

int main(void){
    File_header header; //Variable to store the 24-byte file header

    //Calls header_checker function from io.c
   if (header_checker("adc_sensor_log.bin", &header) == 0) {
       printf("Header validation failed\n");
       return EXIT_FAILURE;
   }
    FILE *data_file = fopen("adc_sensor_log.bin", "rb");

    //Moves the file reading to start of the ADC records, from header to the first record
    fseek(data_file, sizeof(File_header), SEEK_SET);

    ADCSample *samples = load_records(data_file, header.Record_count);
    if (samples == NULL) {
        printf("Failed to load ADC records\n");
        fclose(data_file);
        return EXIT_FAILURE;
    }
    printf("ADC records loaded successfully\n");

    //Raw value to voltage function
    voltage_conversion(samples, header.Record_count);

    //creates one results structure for each channel
    Channel_stats channel_stats[header.Channel_count];

    for (uint16_t channel = 0; channel < header.Channel_count; channel++) {
        Channel_stats *stats = channel_stats + channel;
        Compute_channel_stats(samples, header.Record_count, channel, stats);
    }

    //creates one results structure for each channel
    Fault_counts fault_counts[header.Channel_count];

    for (uint16_t channel = 0; channel < header.Channel_count; channel++) {
        Fault_counts *faults = fault_counts + channel;
        Detect_channel_faults(samples, header.Record_count, channel, faults);
    }

    Sequence_issue *sequence_issues = malloc(header.Record_count * sizeof(*sequence_issues));
    uint32_t sequence_issue_count = Check_sampling_integrity(samples,header.Record_count, sequence_issues);

    if (write_results_file("results.txt", &header, channel_stats, fault_counts, sequence_issues, sequence_issue_count) == 0) {

        //The output file could not be opened.
        fclose(data_file);
        free(sequence_issues);
        free(samples);
        return EXIT_FAILURE;
    }
    printf("\nResults written successfully to results.txt\n");

    fclose(data_file);
    free(sequence_issues);
    free(samples);
    return EXIT_SUCCESS;
}