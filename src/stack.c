#include "stack.h"

#include <stdlib.h>

Stack *stack_init() {
    Stack *stack = malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void stack_push(Stack *stack, Token token) {
    StackNode *node = malloc(sizeof(StackNode));
    node->data = token;
    node->next = stack->top;
    stack->top = node;
}

Token stack_pop(Stack *stack) {
    if (stack->top == NULL) {
        Token empty = {TOKEN_ERROR, ""};
        return empty;
    }
    StackNode *node = stack->top;
    Token token = node->data;
    stack->top = node->next;
    free(node);
    return token;
}

Token stack_peek(Stack *stack) {
    if (stack->top == NULL) {
        Token empty = {TOKEN_ERROR, ""};
        return empty;
    }
    return stack->top->data;
}

int stack_is_empty(Stack *stack) { return stack->top == NULL; }

void stack_free(Stack *stack) {
    while (!stack_is_empty(stack)) {
        stack_pop(stack);
    }
    free(stack);
}