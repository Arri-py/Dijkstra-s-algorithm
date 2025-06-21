#ifndef STACK_H
#define STACK_H

#include "lexer.h"

typedef struct StackNode {
    Token data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} Stack;

Stack *stack_init();
void stack_push(Stack *stack, Token token);
Token stack_pop(Stack *stack);
Token stack_peek(Stack *stack);
int stack_is_empty(Stack *stack);
void stack_free(Stack *stack);

#endif