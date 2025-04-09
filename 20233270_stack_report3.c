#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
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


void push(Stack* s, int value) {
    s->data[++(s->top)] = value;
}


int pop(Stack* s) {
    if (isEmpty(s)) return 0;
    return s->data[(s->top)--];
}


int peek(Stack* s) {
    if (isEmpty(s)) return 0;
    return s->data[s->top];
}


int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isdigit(ch)) {
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            push(&s, ch);
        }
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s); 
        }
        else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);
            }
            push(&s, ch);
        }
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';
}


int evaluatePostfix(char* postfix) {
    Stack s;
    initStack(&s);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isdigit(ch)) {
            push(&s, ch - '0'); 
        }
        else {
            int val2 = pop(&s);
            int val1 = pop(&s);
            switch (ch) {
                case '+': push(&s, val1 + val2); break;
                case '-': push(&s, val1 - val2); break;
                case '*': push(&s, val1 * val2); break;
                case '/': push(&s, val1 / val2); break;
            }
        }
    }

    return pop(&s);
}

int main(void) {
    char infix[MAX];
    char postfix[MAX];

    printf("중위표기식 입력: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("후위표기식: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("계산 결과: %d\n", result);

    return 0;
}
