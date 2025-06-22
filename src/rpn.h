#ifndef RPN_H
#define RPN_H

#include "lexer.h"
#include "stack.h"

#define MAX_TOKENS 256

typedef struct {
    Token *tokens;
    int size;
    int capacity;
} RPNExpression;

RPNExpression *shunting_yard(Lexer *lexer);
void rpn_free(RPNExpression *expr);
int get_precedence(const char *op);
int is_right_associative(const char *op);

#endif