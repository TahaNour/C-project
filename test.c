#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 512
#define MAX_OUTPUT 512

void run_test(const char *dataset_path, const char *program_path) {
    FILE *file = fopen(dataset_path, "r");
    if (!file) {
        perror("Unable to open dataset file");
        return;
    }

    char line[MAX_LINE];
    int total_tests = 0, passed_tests = 0;

    while (fgets(line, sizeof(line), file)) {
        char long_url[MAX_LINE], expected_output[MAX_LINE];
        if (sscanf(line, "%s %s", long_url, expected_output) != 2) {
            fprintf(stderr, "Invalid format in test dataset: %s\n", line);
            continue;
        }

        total_tests++;

        // Command to run your main program with "encode"
        char command[MAX_LINE];
        snprintf(command, sizeof(command), "%s encode \"%s\"", program_path, long_url);

        // Open the process and read its output
        FILE *pipe = popen(command, "r");
        if (!pipe) {
            perror("Failed to run the program");
            fclose(file); // Ensure file is closed before returning
            return;
        }

        char program_output[MAX_OUTPUT];

        // Read the output from the program
        if (fgets(program_output, sizeof(program_output), pipe)) {
            // Remove trailing newline, if any
            program_output[strcspn(program_output, "\n")] = 0;

            // Compare the expected and actual outputs
            if (strstr(program_output, expected_output)) {
                printf("PASS: %s -> %s\n", long_url, expected_output);
                passed_tests++;
            } else {
                printf("FAIL: %s\n", long_url);
                printf("  Expected: %s\n", expected_output);
                printf("  Got: %s\n", program_output);
            }
        } else {
            fprintf(stderr, "No output from the program for %s\n", long_url);
        }

        pclose(pipe);
    }

    fclose(file);

    // Summary of results
    printf("\nTotal Tests: %d, Passed: %d, Failed: %d\n",
           total_tests, passed_tests, total_tests - passed_tests);
}

int main() {
    const char *dataset_path = "verified_encode.txt";
    const char *program_path = ".\\main.exe";  // Updated path for Windows

    printf("Running tests...\n");
    run_test(dataset_path, program_path);

    return 0;
}