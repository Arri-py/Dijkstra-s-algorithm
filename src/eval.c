#include "eval.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token process_variable(double x) {
    Token num_token = {TOKEN_NUMBER, ""};
    snprintf(num_token.value, sizeof(num_token.value), "%f", x);
    return num_token;
}

double eval_function(Token token, Stack *stack) {
    if (stack_is_empty(stack)) return NAN;
    double a = atof(stack_pop(stack).value);
    if (strcmp(token.value, "sin") == 0)
        return sin(a);
    else if (strcmp(token.value, "cos") == 0)
        return cos(a);
    else if (strcmp(token.value, "tan") == 0)
        return tan(a);
    else if (strcmp(token.value, "sqrt") == 0)
        return sqrt(a);
    else if (strcmp(token.value, "ln") == 0)
        return log(a);
    else
        return NAN;
}

double eval_operator(Token token, Stack *stack) {
    if (stack_is_empty(stack)) return NAN;
    double b = atof(stack_pop(stack).value);
    if (stack_is_empty(stack)) return NAN;
    double a = atof(stack_pop(stack).value);

    if (strcmp(token.value, "+") == 0)
        return a + b;
    else if (strcmp(token.value, "-") == 0)
        return a - b;
    else if (strcmp(token.value, "*") == 0)
        return a * b;
    else if (strcmp(token.value, "/") == 0)
        return a / b;
    else if (strcmp(token.value, "^") == 0)
        return pow(a, b);
    else
        return NAN;
}

double eval_rpn(RPNExpression *expr, double x) {
    Stack *stack = stack_init();
    for (int i = 0; i < expr->size; i++) {
        Token token = expr->tokens[i];
        if (token.type == TOKEN_NUMBER) {
            stack_push(stack, token);
        } else if (token.type == TOKEN_VARIABLE) {
            stack_push(stack, process_variable(x));
        } else if (token.type == TOKEN_FUNCTION) {
            double res = eval_function(token, stack);
            Token res_token = {TOKEN_NUMBER, ""};
            snprintf(res_token.value, sizeof(res_token.value), "%f", res);
            stack_push(stack, res_token);
        } else if (token.type == TOKEN_OPERATOR) {
            double res = eval_operator(token, stack);
            Token res_token = {TOKEN_NUMBER, ""};
            snprintf(res_token.value, sizeof(res_token.value), "%f", res);
            stack_push(stack, res_token);
        }
    }
    if (stack_is_empty(stack)) {
        stack_free(stack);
        return NAN;
    }
    double result = atof(stack_pop(stack).value);
    stack_free(stack);
    return result;
}