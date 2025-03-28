#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calculateAverage(int scores[], int size);
int getStudentScore(int scores[], int size, int studentNumber);
void printScore(int scores[], int size, double average, int option);
void deleteStudent(int* scores, int* size, int studentNumber);

int main() {
    int* scores;
    int size = 0;
    int capacity = 30;
    int choice, studentNumber;

    scores = (int*)malloc(capacity * sizeof(int));
    if (!scores) {
        printf("allocation error\n");
        return 1;
    }

    srand(time(0));
    for (int i = 0; i < capacity; i++) {
        scores[i] = rand() % 101;
        size++;
    }
    printf("입력 완료\n");

    while (1) {
        printf("---학생 성적 관리 프로그램---\n");
        printf("1. 학생정보 추가\n");
        printf("2. 학생정보 삭제\n");
        printf("3. 학생정보 검색\n");
        printf("4. 학생정보 출력(옵션 : 0,1,2)\n");
        printf("5. 프로그램 종료\n");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            if (size >= capacity) {
                capacity += 10;
                int* newScores = realloc(scores, capacity * sizeof(int));
                if (!newScores) {
                    printf("allocation error\n");
                    free(scores);
                    return 1;
                }
                scores = newScores;
            }
            int newScore = rand() % 101;
            scores[size] = newScore;
            printf("새로운 학생 추가 : 번호 - %d, 점수 - %d\n", size + 1, newScore);
            size++;
            break;
        case 2:
            printf("삭제할 학생 번호 입력(1 ~ %d): ", size);
            scanf_s("%d", &studentNumber);
            deleteStudent(scores, &size, studentNumber);
            break;
        case 3:
            printf("검색할 학생 번호 입력(1 ~ %d): ", size);
            scanf_s("%d", &studentNumber);
            int score = getStudentScore(scores, size, studentNumber);
            if (score != -1) printf("%d번 학생 점수 : %d\n", studentNumber, score);
            else printf("해당 학생은 없는 학생입니다.\n");
            break;
        case 4:
            printf("출력 옵션 입력 (0, 1, 2): ");
            int option;
            scanf_s("%d", &option);
            double average = calculateAverage(scores, size);
            printScore(scores, size, average, option);
            break;
        case 5:
            free(scores);
            printf("프로그램 종료\n");
            return 0;
        default:
            printf("잘못된 입력\n");
            break;
        }
    }

    return 0;
}

void deleteStudent(int* scores, int* size, int studentNumber) {
    if (studentNumber < 1 || studentNumber > *size) {
        printf("학생번호 오류\n");
        return;
    }
    if (scores[studentNumber - 1] == -1) {
        printf("없는 학생입니다.\n");
    }
    else {
        scores[studentNumber - 1] = -1;
        printf("%d 학생 삭제완료\n", studentNumber);
    }
}

double calculateAverage(int scores[], int size) {
    if (size == 0) return 0;
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    return sum / size;
}

int getStudentScore(int scores[], int size, int studentNumber) {
    if (studentNumber < 1 || studentNumber > size) return -1;
    return scores[studentNumber - 1];
}

void printScore(int scores[], int size, double average, int option) {
    printf("학생 점수 평균: %.2f\n", average);
    for (int i = 0; i < size; i++) {
        if (scores[i] != -1) {
            if (option == 0) {
                printf("학생 %d 점수: %d\n", i + 1, scores[i]);
            }
            else if (option == 1 && scores[i] > average) {
                printf("학생 %d 점수: %d\n", i + 1, scores[i]);
            }
            else if (option == 2 && scores[i] <= average) {
                printf("학생 %d 점수: %d\n", i + 1, scores[i]);
            }
        }
    }
}

// 배열의 값을 앞으로 이동 (삭제)
void deleteStudent(int* scores, int* size, int studentNumber) { 
    if (studentNumber < 1 || studentNumber > *size) {
        printf("학생번호 오류\n");
        return;
    }
    for (int i = studentNumber - 1; i < *size - 1; i++) {
        scores[i] = scores[i + 1];
    }
    (*size)--; // 크기 감소
}


// 특정 값을 -1로 설정 (삭제)
void deleteStudent(int* scores, int* size, int studentNumber) {
    if (studentNumber < 1 || studentNumber > *size) {
        printf("학생번호 오류\n");
        return;
    }
    scores[studentNumber - 1] = -1; // 전학으로 표시
}

//배열 크기 확장 (추가)
void addStudents(int** scores, int* size, int* capacity, int newStudents) {
    while (*size + newStudents > *capacity) {
        *capacity += 10; // 여유 공간 확보
        *scores = realloc(*scores, (*capacity) * sizeof(int));
        if (!*scores) {
            printf("allocation error\n");
            exit(1);
        }
    }
    for (int i = 0; i < newStudents; i++) {
        (*scores)[*size] = rand() % 101; // 임의의 점수 추가
        (*size)++;
    }
}
