ADC Sensor Data Processor:

This project is a C99 command-line program that processes a binary data file
produced by a four-channel, 12-bit analogue-to-digital converter.

The program:

- reads and validates the binary file header;
- dynamically allocates memory for the ADC records;
- converts raw ADC readings into voltage;
- calculates statistics for each channel;
- detects voltage and sensor fault conditions;
- checks sequence numbers for missing or out-of-order records;
- writes the findings to 'results.txt'.

Compile and Run Using CLion:

1. Open CLion.
2. Select Open and open the main 'ADC' project folder.
3. Wait for CLion to load the CMakeLists.txt file.
4. Make sure 'adc_sensor_log.bin' is in the main project folder.
5. Select Run, Edit Configurations.
6. Select the 'ADC' application configuration.
7. Enter the following under Program arguments:

adc_sensor_log.bin

8. Set the working directory to the main ADC project folder. In CLion this can
   normally be entered as:

$ProjectFileDir$

9. Select Build, Build Project to compile the program.
10. Click the green Run button.
11. The completed analysis will be written to 'results.txt'.

Compile and Run Using GCC:

Open PowerShell or a terminal in the main ADC project folder.

Compile the source files using:

powershell:
gcc -std=c99 main.c ADC.c io.c stats.c -o ADC.exe -lm

This command:

- selects the C99 language standard using `-std=c99`;
- compiles all four `.c` source files;
- creates an executable named `ADC.exe`;
- links the mathematics library using `-lm`.

Run the program using:

powershell:
.\ADC.exe adc_sensor_log.bin


The first command-line argument supplies the name of the binary input file.
The program creates or overwrites 'results.txt' in the current working directory.

Project Files:

- 'main.c' — program entry point and function coordination
- 'ADC.c' / 'ADC.h' — voltage conversion, channel analysis and integrity checking
- 'io.c' / 'io.h' — binary input, header validation and results-file output
- 'stats.c' / 'stats.h' — individual statistical calculation functions
- 'CMakeLists.txt' — CMake build configuration
- 'adc_sensor_log.bin' — provided binary dataset
- 'results.txt' — generated analysis report

GitHub Repository:

[ADC GitHub repository](https://github.com/WesDebroize/ADC)