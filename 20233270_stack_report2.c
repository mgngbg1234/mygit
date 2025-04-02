#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  

typedef struct {
    char data[MAX];
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

void push(Stack* s, char value) {
    if (isFull(s)) {
        printf("Stack overflow! Cannot push %c\n", value);
        return;
    }
    s->data[++(s->top)] = value;
}

char pop(Stack* s) {
    if (isEmpty(s)) {
        return '\0'; 
    }
    return s->data[(s->top)--];
}

char peek(Stack* s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->data[s->top];
}

int isMatchingPair(char opening, char closing) {
    if (opening == '(' && closing == ')') return 1;
    if (opening == '{' && closing == '}') return 1;
    if (opening == '[' && closing == ']') return 1;
    return 0;
}

int checkParentheses(const char* str) {
    Stack s;
    initStack(&s);

    for (int i = 0; i < strlen(str); i++) {
        char current = str[i];

        if (current == '(' || current == '{' || current == '[') {
            push(&s, current);
        }
        else if (current == ')' || current == '}' || current == ']') {
            if (isEmpty(&s) || !isMatchingPair(pop(&s), current)) {
                return 0; 
            }
        }
    }
    return isEmpty(&s); 
}

int main() {
    char str[MAX];
    printf("문자열을 입력하세요: ");
    fgets(str, MAX, stdin);

    
    str[strcspn(str, "\n")] = 0;

    if (checkParentheses(str)) {
        printf("유효한 괄호\n");
    }
    else {
        printf("유효하지 않은 괄호\n");
    }

    return 0;
}
