#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../C-project/main.c"  // Relative path to main.c in the src folder

// Function to run the tests from the file
void run_tests(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    char long_url[1024], short_url[100], generated_short_url[100];

    // Read each line from the file
    while (fscanf(file, "%s %s", long_url, short_url) != EOF) {
        encode(long_url, generated_short_url);  // Call encode function with the long URL
        assert(strcmp(generated_short_url, short_url) == 0);  // Compare with the expected short URL
        printf("Test passed for: %s\n", long_url);  // If the test passes
    }

    fclose(file);
}

int main() {
    // Run tests on test.txt (relative path)
    run_tests("verified_encode.txt");
    return 0;
}