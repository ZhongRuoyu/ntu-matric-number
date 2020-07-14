/* Copyright (c) 2020 Zhong Ruoyu */
/* This program uses a number of actual data sets to reverse-engineer the algorithm 
 * for calculating the checksum of NTU matriculation numbers. To find out more, 
 * visit https://github.com/ZhongRuoyu/ntu-matric-number */

#include <stdio.h>

#define MIN 1
#define MAX 10
#define OFFMIN 0
#define OFFMAX 10
#define DIGITCOUNT 7
#define SAMPLECOUNT 16

struct matric {char type; int num; char code;};

const struct matric SAMPLES[SAMPLECOUNT] = {
    /* For privacy concerns, only sample data is displayed.
     * To actually calculate the results, replace the sample data sets with actual ones. */
    {'U', 1813141, 'E'}, {'U', 1825926, 'E'}, {'U', 1835358, 'C'}, {'U', 1849793, 'L'}, {'U', 1912384, 'A'},
    {'U', 1926264, 'B'}, {'U', 1933383, 'K'}, {'U', 1942795, 'A'}, {'U', 2010288, 'D'}, {'U', 2024197, 'H'},
    {'U', 2031693, 'B'}, {'U', 2049937, 'H'},
    {0} // If SAMPLECOUNT > actual number of sample data sets, ending with {0} tells the program to stop here.
};

int validate(int *, int);
int weightedsum(int, int *);

const char ALPHA[11] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L'};

int main(void)
{
    int w[DIGITCOUNT];
    int tryCount = 0, resultCount = 0;
    int offset;

    printf("Calculating...\n\n");
    // For shorter output, use the following line instead.
    // printf("Set #\tw[0]\tw[1]\tw[2]\tw[3]\tw[4]\tw[5]\tw[6]\toffset\n");
    for (w[0] = MIN; w[0] <= MAX; w[0]++) {
        for (w[1] = MIN; w[1] <= MAX; w[1]++) {
            for (w[2] = MIN; w[2] <= MAX; w[2]++) {
                for (w[3] = MIN; w[3] <= MAX; w[3]++) {
                    for (w[4] = MIN; w[4] <= MAX; w[4]++) {
                        for (w[5] = MIN; w[5] <= MAX; w[5]++) {
                            for (w[6] = MIN; w[6] <= MAX; w[6]++) {
                                for (offset = OFFMIN; offset <= OFFMAX; offset++) {
                                    tryCount++;
                                    if (validate(w, offset)) {
                                        printf("Try #%d: Set #%d found.\n", tryCount, ++resultCount);
                                        printf("w[0]\tw[1]\tw[2]\tw[3]\tw[4]\tw[5]\tw[6]\toffset\n");
                                        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n\n", w[0], w[1], w[2], w[3], w[4], w[5], w[6], offset);
                                        printf("Still calculating...\n");
                                        // For shorter output, use the following line instead.
                                        // printf("#%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ++resultCount, w[0], w[1], w[2], w[3], w[4], w[5], w[6], offset);
                                    };
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("\nCalculation finished. %d sets found in %d tries.\n\n", resultCount, tryCount);

    return 0;
}

int validate(int *w, int offset)
{
    int sum;
    int remainder;
    for (int i = 0; i < SAMPLECOUNT; i++) {
        if (SAMPLES[i].type == 0) return 1;
        sum = weightedsum(SAMPLES[i].num, w) + offset;
        remainder = sum % 11;
        if (ALPHA[remainder] != SAMPLES[i].code) return 0;
    }
    return 1;
}

int weightedsum(int num, int *w)
{
    int sum = 0;
    for (int i = 1; i <= DIGITCOUNT; i++) {
        sum += (num % 10) * (w[DIGITCOUNT - i]);
        num /= 10;
    }
    return sum;
}
