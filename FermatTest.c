#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

int modulo(int base, int exponent, int mod) {
    int x = 1;
    int y = base;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}
 
bool isPrime(int n, int k) {
    int i;
    if (n == 1) {
        return false;
    }
    for (i = 0; i < k; i++) {
        int a = rand() % (n - 1) + 1;
        if (modulo(a, n - 1, n) != 1) {
            return false;
        }
    }
    return true;
}

int main() {
    // Create file name strings
    char inFileName[256];
    strcpy(inFileName, "test.in");
    char outFileName[256];
    strcpy(outFileName, "test.out");
    
    // Open the files
    FILE *inFilePtr = fopen(inFileName, "r");
    FILE *outFilePtr = fopen(outFileName, "w");
    
    // Get the number of elements in the sequence
    int N;
    fscanf(inFilePtr, "%d\n", &N);
    
    // Create an array to store the sequence
    int seq[N];
    
    // Parse the sequence
    for (int i = 0; i < N; i++) {
        fscanf(inFilePtr, "%d", &seq[i]);
    }

    // Get the start time
    struct timeval startTime;
    gettimeofday(&startTime, NULL);
    
    // Count the number of prime elements in the sequence
    int M = 0;
    for (int i = 0; i < N; i++) {
        if (isPrime(seq[i], 10)) {
            M++;
        }
    }

    // Get the end time
    struct timeval endTime;
    gettimeofday(&endTime, NULL);
    
    // Get the time difference in milliseconds
    double timeInMilliseconds = 
        (endTime.tv_sec - startTime.tv_sec) * 1000.0 + 
        (endTime.tv_usec - startTime.tv_usec) / 1000.0;
    
    // Get the memory used
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    double memoryInKilobytes = (double)usage.ru_maxrss / 1024;
    
    // Print the time and memory used
    printf(inFileName);
    printf("Time: %fms\n", timeInMilliseconds);
    printf("Memory: %fkB\n", memoryInKilobytes);
    
    // Print the number of prime elements
    fprintf(outFilePtr, "%d\n", M);
    
    // Print the prime elements
    for (int i = 0; i < N; i++) {
        if (isPrime(seq[i], 10)) {
            fprintf(outFilePtr, "%d ", seq[i]);
        }
    }
    fprintf(outFilePtr, "\n");
    
    // Close the files
    fclose(inFilePtr);
    fclose(outFilePtr);
    
    return 0;
}
