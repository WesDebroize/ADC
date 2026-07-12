#include <stdio.h>
#include <stdlib.h>

#include "ADC.h"
#include "io.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_filename = argv[1];

    File_header header;

    if (header_checker(input_filename, &header) == 0) {
        printf("Header validation failed\n");
        return EXIT_FAILURE;
    }

    FILE *data_file = fopen(input_filename, "rb");

    if (data_file == NULL) {
        perror("Could not reopen input file");
        return EXIT_FAILURE;
    }

    if (fseek(data_file, sizeof(File_header), SEEK_SET) != 0) {
        perror("Could not move to the first record");
        fclose(data_file);
        return EXIT_FAILURE;
    }

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

    if (sequence_issues == NULL) {
        printf("Could not allocate memory for sequence issues\n");
        fclose(data_file);
        free(samples);
        return EXIT_FAILURE;
    }
    uint32_t sequence_issue_count = Check_sampling_integrity(samples, header.Record_count, sequence_issues);

    if (write_results_file("results.txt", &header, channel_stats, fault_counts, sequence_issues, sequence_issue_count) == 0) {

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