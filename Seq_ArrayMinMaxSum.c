#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i, min, max, sum;
    int A[100];
    srand(1234);
    for (i = 0; i < 100; i++) {
        A[i] = rand()%1000;
    }

    min = 0;
    max = 0;
    sum = 0;
    for (i = 0; i < 100; i++) {
        sum += A[i];
        if (A[i] < min) min = A[i];
        if (A[i] > max) max = A[i];
    }
    printf("Sequential: min=%d max=%d sum=%d\n", min, max, sum);
}