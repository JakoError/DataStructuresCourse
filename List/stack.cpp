//
// Created by JakoError on 2021/3/30.
//
#include <cstdio>
#include <cstdlib>
#include "stack.h"

bool push(Stack* S, ElemType x){
    if (S->top == Stack_Size-1)
        return false;
    S->elem[++S->top] = x;
    return true;
}
bool pop(Stack* S, ElemType *x){
    if (S->top == -1)
        return false;
    *x = S->elem[S->top--];
    return true;
}

void init_stack(Stack *S){
    S->top = -1;
}


// +，-，*, /, %
int compute_reverse_polish_notation(char *str) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    init_stack(stack);
    char op[] = {'+', '-', '*', '/', '%'};
    while (str[0] != '\0') {
        int index = -1;
        for (int i = 0; i < 5; ++i)
            if (op[i] == str[0]) {
                index = i;
                break;
            }
        if (index == -1){
            int num;
            sscanf(str, "%d", &num);
            push(stack,num);
            int i = 0;
            while (str[i]!='\0' && str[i++]!=' ');
            str = &str[i];
        }else{
            int a, b, result;
            a = b = result = 0;
            pop(stack, &b);
            pop(stack, &a);
            if (index == 0)
                result = a + b;
            else if (index == 1)
                result = a - b;
            else if (index == 2)
                result = a * b;
            else if (index == 3)
                result = a / b;
            else if (index == 4)
                result = a % b;
            push(stack, result);
            if (str[1]!='\0')
                str = &str[2];
            else
                str = &str[1];
        }
    }
    int result;
    pop(stack,&result);
    return result;
}