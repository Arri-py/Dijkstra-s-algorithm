#include "eval.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double eval_rpn(RPNExpression *expr, double x) {
    Stack *stack = stack_init();
    for (int i = 0; i < expr->size; i++) {
        Token token = expr->tokens[i];
        if (token.type == TOKEN_NUMBER) {
            stack_push(stack, token);
        } else if (token.type == TOKEN_VARIABLE) {
            Token num_token = {TOKEN_NUMBER, ""};
            snprintf(num_token.value, sizeof(num_token.value), "%f", x);
            stack_push(stack, num_token);
        } else if (token.type == TOKEN_OPERATOR || token.type == TOKEN_FUNCTION) {
            if (stack_is_empty(stack)) return NAN;
            double a, b, res;
            if (token.type == TOKEN_FUNCTION) {
                a = atof(stack_pop(stack).value);
                if (strcmp(token.value, "sin") == 0)
                    res = sin(a);
                else if (strcmp(token.value, "cos") == 0)
                    res = cos(a);
                else if (strcmp(token.value, "tan") == 0)
                    res = tan(a);
                else if (strcmp(token.value, "sqrt") == 0)
                    res = sqrt(a);
                else if (strcmp(token.value, "ln") == 0)
                    res = log(a);
                else
                    return NAN;
            } else {
                b = atof(stack_pop(stack).value);
                a = atof(stack_pop(stack).value);
                if (strcmp(token.value, "+") == 0)
                    res = a + b;
                else if (strcmp(token.value, "-") == 0)
                    res = a - b;
                else if (strcmp(token.value, "*") == 0)
                    res = a * b;
                else if (strcmp(token.value, "/") == 0)
                    res = a / b;
                else if (strcmp(token.value, "^") == 0)
                    res = pow(a, b);
                else
                    return NAN;
            }
            Token res_token = {TOKEN_NUMBER, ""};
            snprintf(res_token.value, sizeof(res_token.value), "%f", res);
            stack_push(stack, res_token);
        }
    }
    if (stack_is_empty(stack)) return NAN;
    double result = atof(stack_pop(stack).value);
    stack_free(stack);
    return result;
}