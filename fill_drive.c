#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// CONFIGURE THIS PATH TO YOUR USB DRIVE LETTER
// Example Windows: "E:\\test_fill.dat"
// Example Linux:   "/mnt/usb/test_fill.dat"
// #define FILE_PATH "‪D:\\test_fill.dat"
#define FILE_PATH "Z:\\test_fill1.dat"

// Buffer size: 10 MB (Larger buffer = Faster write speed)
#define BUFFER_SIZE (10 * 1024 * 1024)

int main() {
    FILE *fp;
    unsigned char *buffer;
    unsigned long long total_written = 0;
    size_t bytes_written;
    time_t start_time, current_time;

    printf("Starting High-Speed Fill Test...\n");
    printf("Target: %s\n", FILE_PATH);

    // 1. Allocate Memory (10 MB)
    buffer = (unsigned char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        printf("Error: Could not allocate memory.\n");
        return 1;
    }

    // 2. Fill buffer with all 1s (0xFF) - "The White Data"
    memset(buffer, 0xFF, BUFFER_SIZE);

    // 3. Open File
    fp = fopen(FILE_PATH, "wb");
    if (fp == NULL) {
        printf("Error: Could not open file on drive. Check drive letter.\n");
        free(buffer);
        return 1;
    }

    start_time = time(NULL);

    // 4. Write Loop
    while (1) {
        bytes_written = fwrite(buffer, 1, BUFFER_SIZE, fp);

        if (bytes_written < BUFFER_SIZE) {
            // If we write less than requested, the disk is likely full or errored
            printf("\nStopping: Write failed or Disk Full.\n");
            break;
        }

        total_written += bytes_written;

        // Print progress every 1 GB (approx 100 loops)
        if ((total_written % (1024 * 1024 * 1024)) < BUFFER_SIZE) {
            double gb = (double)total_written / (1024 * 1024 * 1024);
            printf("\rWritten: %.2f GB... ", gb);
            fflush(stdout); // Force update screen
        }
    }

    // 5. Cleanup
    fclose(fp);
    free(buffer);

    printf("\nTest Complete.\n");
    printf("Total Data Written: %.2f GB\n", (double)total_written / (1024 * 1024 * 1024));

    return 0;
}
