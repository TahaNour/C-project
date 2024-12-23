#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h" // Relative path to main.c in the src folder

// Function to run a single test case
bool run_test(FILE *file, int test_case_num)
{
    char long_url[1024], expected_short_url[100], generated_short_url[100];

    // Read inputs (long_url) and expected short URL
    if (fscanf(file, "%s %s", long_url, expected_short_url) != 2)
    {
        if (feof(file))
        {
            // End of file reached, no more test cases
            return false;
        }
        printf("Test case %d: Error reading dataset file\n", test_case_num);
        return false;
    }

    // Call the encode function
    encode(long_url, generated_short_url);

    // Compare the generated result with the expected result
    if (strcmp(generated_short_url, expected_short_url) == 0)
    {
        printf("Test case %d: Passed (%s -> %s)\n", test_case_num, long_url, generated_short_url);
        return true;
    }
    else
    {
        printf("Test case %d: Failed (%s -> %s, expected %s)\n", test_case_num, long_url, generated_short_url, expected_short_url);
        return false;
    }
}

int main()
{
    FILE *file = fopen("verified_encode.txt", "r");
    if (file == NULL)
    {
        perror("Error opening dataset file");
        return 1;
    }

    int test_case_num = 0;
    int passed = 0, failed = 0;

    printf("Running tests...\n");

    while (!feof(file))
    {
        test_case_num++;
        // Run each test and count passed/failed
        if (!run_test(file, test_case_num))
        {
            // If run_test returns false due to EOF, exit loop
            if (feof(file))
                break;
            failed++;
        }
        else
        {
            passed++;
        }
    }

    fclose(file);

    printf("\nTotal tests: %d | Passed: %d | Failed: %d\n", passed + failed, passed, failed);

    return (failed == 0) ? 0 : 1; // Return non-zero exit code if any test failed
}
