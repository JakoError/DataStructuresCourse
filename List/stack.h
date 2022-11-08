//
// Created by JakoError on 2021/3/30.
//

#ifndef DATASTRUCTURE_STACK_H
#define DATASTRUCTURE_STACK_H
#define Stack_Size 50
#define ElemType int
typedef struct {
    ElemType elem[Stack_Size];
    int top;
}Stack;

bool push(Stack* S, ElemType x);
bool pop(Stack* S, ElemType *x);
void init_stack(Stack *S);
int compute_reverse_polish_notation(char *str);
#endif //DATASTRUCTURE_STACK_H
