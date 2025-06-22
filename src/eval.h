#ifndef EVAL_H
#define EVAL_H

#include <math.h>

#include "rpn.h"

double eval_rpn(RPNExpression *expr, double x);
Token process_variable(double x);
double eval_function(Token token, Stack *stack);
double eval_operator(Token token, Stack *stack);

#endif