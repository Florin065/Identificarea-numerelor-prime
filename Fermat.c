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

double memorie = 0;
double timp = 0;

//This function calculates the modulo of a base and exponent, modulo a certain value.
int modulo(int base, int exponent, int mod) {
    int x = 1; //Initialize the result to 1
    int y = base; //Set y to the base number
    while (exponent > 0) { //Loop while the exponent is greater than 0
        if (exponent % 2 == 1) //If the exponent is odd
            x = (x * y) % mod; //Multiply x and y and modulo it with the given mod
        y = (y * y) % mod; //Square y and modulo it with the given mod
        exponent = exponent / 2; //Divide the exponent by 2
    }
    return x % mod; //Return x modulo the given mod
}

//This function checks if a number is prime using the Miller-Rabin algorithm.
bool isPrime(int n, int k) {
    int i; //Initialize a counter
    if (n == 1) { //If the number is one, return false
        return false;
    }
    for (i = 0; i < k; i++) { //Loop k times
        int a = rand() % (n - 1) + 1; //Generate a random number in the range of 1 to n-1
        if (modulo(a, n - 1, n) != 1) { //If the modulo of a, n-1, and n is not 1
            return false; //Return false
        }
    }
    return true; //If the algorithm passes for k times, return true
}

int main() {
    // Open the directory containing the input files
    DIR *inDir;
    struct dirent *inFile;
    inDir = opendir("in");
    
    // Create directory for output
    mkdir("outFermat", 0777);
    
    // Iterate through the input files
    while ((inFile = readdir(inDir)) != NULL) {
        
        // Check if the file is an input file
        if (strstr(inFile->d_name, ".in") != NULL) {
            
            // Create file name strings
            char inFileName[256];
            strcpy(inFileName, "in/");
            strcat(inFileName, inFile->d_name);
            char outFileName[256];
            strcpy(outFileName, "outFermat/");
            strcat(outFileName, strtok(inFile->d_name, "."));
            strcat(outFileName, ".out");
            
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
                if (isPrime(seq[i], 1000)) {
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
            
            memorie += memoryInKilobytes;
            timp += timeInMilliseconds;

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
            
        }
    }
    
    // Close the directory
    closedir(inDir);

    timp /= 20;
    memorie /= 20;
    printf("medie timp executare: %fms\n", timp);
    printf("medie memorie consumată %fkB\n", memorie);
    
    return 0;
}
