#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>

#define MAX 100  

typedef struct {
    int data[MAX];
    int top;  
} Stack;


void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}


void push(Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack overflow! Cannot push %d\n", value);
        return;
    }
    s->data[++(s->top)] = value;
}


int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow! Cannot pop\n");
        return -1;  
    }
    return s->data[(s->top)--];
}


int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty! Cannot peek\n");
        return -1; 
    }
    return s->data[s->top];
}


void display(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack contents: ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

int main() {
    Stack s;
    char str[MAX];
    initStack(&s);

    printf("문자열 입력: ");
    fgets(str, MAX, stdin);

    for (int i = 0; str[i] != '\0'; i++)  push(&s, str[i]);
    printf("거꾸로 된 문자열: ");
    while (!isEmpty(&s)) {
        printf("%c",pop(&s));
    }
  


    return 0;
}
