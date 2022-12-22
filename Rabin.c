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

// Utility function to do modular exponentiation.
// It returns (x^y) % p
int power(int x, size_t y, int p)
{
    int res = 1;      // Initialize result
    x %= p;  // Update x if it is more than or
                // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1) {
            res = (res * x) % p;
        }
 
        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}
 
// This function is called for all k trials. It returns
// false if n is composite and returns true if n is
// probably prime.
// d is an odd number such that  d*2 = n-1
// for some r >= 1
bool millerTest(int d, int n)
{
    // Pick a random number in [2..n-2]
    // Corner cases make sure that n > 4
    int a = 2 + rand() % (n - 4);
 
    // Compute a^d % n
    int x = power(a, d, n);
 
    if (x == 1  || x == n-1)
       return true;
 
    // Keep squaring x while one of the following doesn't
    // happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n - 1)
    {
        x = (x * x) % n;
        d *= 2;
 
        if (x == 1) {
            return false;
        }
        if (x == n - 1) {
            return true;
        }
    }
 
    // Return composite
    return false;
}
 
// It returns false if n is composite and returns true if n
// is probably prime.  k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
bool isPrime(int n, int k)
{
    // Corner cases
    if (n <= 1 || n == 4) {
        return false;
    }

    if (n <= 3) {
        return true;
    }
 
    // Find r such that n = 2^d * r + 1 for some r >= 1
    int d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }
 
    // Iterate given number of 'k' times
    for (int i = 0; i < k; i++) {
                 if (!millerTest(d, n)) {
              return false;
         }
    }
 
    return true;
}

int main() {
    // Open the directory containing the input files
    DIR *inDir;
    struct dirent *inFile;
    inDir = opendir("in");
    
    // Create directory for output
    mkdir("outRabin", 0777);
    
    // Iterate through the input files
    while ((inFile = readdir(inDir)) != NULL) {
        
        // Check if the file is an input file
        if (strstr(inFile->d_name, ".in") != NULL) {
            
            // Create file name strings
            char inFileName[256];
            strcpy(inFileName, "in/");
            strcat(inFileName, inFile->d_name);
            char outFileName[256];
            strcpy(outFileName, "outRabin/");
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
