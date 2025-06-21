#ifndef RPN_H
#define RPN_H

#include "lexer.h"
#include "stack.h"

typedef struct {
    Token *tokens;
    int size;
} RPNExpression;

RPNExpression *shunting_yard(Lexer *lexer);
void rpn_free(RPNExpression *expr);

#endif