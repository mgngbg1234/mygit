#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10  

typedef struct {
    char documentName[50];
    int numPages;
} PrintJob;

typedef struct {
    PrintJob queue[SIZE];
    int front;
    int rear;
} PrintQueue;


void initQueue(PrintQueue* q) {
    q->front = 0;
    q->rear = 0;
}


bool isEmpty(PrintQueue* q) {
    return q->front == q->rear;
}

bool isFull(PrintQueue* q) {
    return (q->rear + 1) % SIZE == q->front;
}


bool enqueue(PrintQueue* q, char* documentName, int numPages) {
    if (isFull(q)) {
        printf("대기열이 가득 찼습니다. 작업을 추가할 수 없습니다.\n");
        return false;
    }
    if (numPages > 50) {
        printf("페이지 수가 50장을 초과하는 문서는 추가할 수 없습니다.\n");
        return false;
    }

    strcpy(q->queue[q->rear].documentName, documentName);
    q->queue[q->rear].numPages = numPages;
    q->rear = (q->rear + 1) % SIZE;
    printf("작업 '%s' (%d 페이지)가 대기열에 추가되었습니다.\n", documentName, numPages);
    return true;
}


PrintJob dequeue(PrintQueue* q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다. 작업이 없습니다.\n");
        PrintJob emptyJob = { "", 0 };
        return emptyJob;
    }

    PrintJob job = q->queue[q->front];
    q->front = (q->front + 1) % SIZE;
    return job;
}


bool cancelJob(PrintQueue* q, const char* documentName) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return false;
    }

    int i = q->front;
    int found = -1;
    while (i != q->rear) {
        if (strcmp(q->queue[i].documentName, documentName) == 0) {
            found = i;
            break;
        }
        i = (i + 1) % SIZE;
    }

    if (found == -1) {
        printf("해당 문서가 없습니다.\n");
        return false;
    }

    
    int next = (found + 1) % SIZE;
    while (next != q->rear) {
        q->queue[found] = q->queue[next];
        found = next;
        next = (next + 1) % SIZE;
    }

   
    q->rear = (q->rear - 1 + SIZE) % SIZE;
    printf("작업 '%s'이(가) 대기열에서 취소되었습니다.\n", documentName);
    return true;
}


void printQueue(PrintQueue* q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }

    printf("현재 대기 중인 작업:\n");
    int i = q->front;
    while (i != q->rear) {
        printf("- %s (%d 페이지)\n", q->queue[i].documentName, q->queue[i].numPages);
        i = (i + 1) % SIZE;
    }
}


void clearQueue(PrintQueue* q) {
    initQueue(q);
    printf("대기열이 초기화되었습니다.\n");
}


int main() {
    PrintQueue q;
    initQueue(&q);

    int choice;
    char documentName[50];
    int numPages;

    while (true) {
        printf("\n1. 작업 추가\n2. 작업 처리\n3. 대기열 출력\n4. 인쇄 취소\n5. 대기열 초기화\n6. 종료\n선택: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("문서 이름: ");
            scanf("%s", documentName);
            printf("페이지 수: ");
            scanf("%d", &numPages);
            enqueue(&q, documentName, numPages);
            break;
        case 2: {
            PrintJob job = dequeue(&q);
            if (strlen(job.documentName) > 0) {
                printf("작업 '%s' (%d 페이지)를 처리 중입니다...\n", job.documentName, job.numPages);
            }
            break;
        }
        case 3:
            printQueue(&q);
            break;
        case 4:
            printf("취소할 문서 이름: ");
            scanf("%s", documentName);
            cancelJob(&q, documentName);
            break;
        case 5:
            clearQueue(&q);
            break;
        case 6:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 입력입니다. 다시 선택해 주세요.\n");
            break;
        }
    }
}
