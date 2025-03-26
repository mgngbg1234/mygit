#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int scores[10];
    int total = 0;
    double average;

    
    srand(time(NULL));

 
    for (int i = 0; i < 10; i++) {
        scores[i] = rand() % 101;  
        total += scores[i];  
    }

    average = (double)total / 10.0;
    printf("전체 학생의 평균 점수: %.2f\n", average);

    return 0;
}
