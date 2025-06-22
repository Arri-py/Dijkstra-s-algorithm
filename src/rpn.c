#include "rpn.h"

#include <stdlib.h>
#include <string.h>

static int handle_number_or_variable(RPNExpression *expr, Token token) {
    if (expr->size >= expr->capacity) {
        int new_capacity = expr->capacity * 2;
        Token *new_tokens = realloc(expr->tokens, new_capacity * sizeof(Token));
        if (!new_tokens) return 0;
        expr->tokens = new_tokens;
        expr->capacity = new_capacity;
    }
    expr->tokens[expr->size++] = token;
    return 1;
}

static int handle_operator(RPNExpression *expr, Stack *op_stack, Token token) {
    while (!stack_is_empty(op_stack)) {
        Token top = stack_peek(op_stack);

        int precedence_condition = 0;
        if (top.type == TOKEN_OPERATOR) {
            int top_prec = get_precedence(top.value);
            int token_prec = get_precedence(token.value);

            if (is_right_associative(token.value)) {
                precedence_condition = (top_prec > token_prec);
            } else {
                precedence_condition = (top_prec >= token_prec);
            }
        }

        if ((top.type == TOKEN_OPERATOR && precedence_condition) || top.type == TOKEN_FUNCTION) {
            if (!handle_number_or_variable(expr, stack_pop(op_stack))) {
                return 0;
            }
        } else {
            break;
        }
    }
    stack_push(op_stack, token);
    return 1;
}

static int handle_right_parenthesis(RPNExpression *expr, Stack *op_stack) {
    while (!stack_is_empty(op_stack) && stack_peek(op_stack).type != TOKEN_LPAREN) {
        if (!handle_number_or_variable(expr, stack_pop(op_stack))) {
            return 0;
        }
    }

    if (stack_is_empty(op_stack)) {
        return 0;
    }

    stack_pop(op_stack);

    if (!stack_is_empty(op_stack) && stack_peek(op_stack).type == TOKEN_FUNCTION) {
        if (!handle_number_or_variable(expr, stack_pop(op_stack))) {
            return 0;
        }
    }
    return 1;
}

static int process_remaining_operators(RPNExpression *expr, Stack *op_stack) {
    while (!stack_is_empty(op_stack)) {
        Token top = stack_pop(op_stack);
        if (top.type == TOKEN_LPAREN) {
            return 0;
        }
        if (!handle_number_or_variable(expr, top)) {
            return 0;
        }
    }
    return 1;
}

RPNExpression *shunting_yard(Lexer *lexer) {
    Stack *op_stack = stack_init();
    if (!op_stack) return NULL;
    RPNExpression *output = calloc(1, sizeof(RPNExpression));
    if (!output) {
        stack_free(op_stack);
        return NULL;
    }
    output->tokens = malloc(MAX_TOKENS * sizeof(Token));
    if (!output->tokens) {
        rpn_free(output);
        stack_free(op_stack);
        return NULL;
    }
    output->capacity = MAX_TOKENS;
    int status = 1;
    Token token;
    while (status && (token = lexer_next_token(lexer)).type != TOKEN_EOF) {
        switch (token.type) {
            case TOKEN_NUMBER:
            case TOKEN_VARIABLE:
                status = handle_number_or_variable(output, token);
                break;
            case TOKEN_FUNCTION:
                stack_push(op_stack, token);
                break;
            case TOKEN_OPERATOR:
                status = handle_operator(output, op_stack, token);
                break;
            case TOKEN_LPAREN:
                stack_push(op_stack, token);
                break;
            case TOKEN_RPAREN:
                status = handle_right_parenthesis(output, op_stack);
                break;
            default:
                status = 0;
        }
    }
    if (status) {
        status = process_remaining_operators(output, op_stack);
    }
    if (!status) {
        rpn_free(output);
        output = NULL;
    }
    stack_free(op_stack);
    return output;
}

void rpn_free(RPNExpression *expr) {
    if (expr) {
        free(expr->tokens);
        free(expr);
    }
}

int get_precedence(const char *op) {
    if (!op) return 0;
    if (strcmp(op, "^") == 0) return 4;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) return 3;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 2;
    return 0;
}

int is_right_associative(const char *op) { return op && strcmp(op, "^") == 0; }