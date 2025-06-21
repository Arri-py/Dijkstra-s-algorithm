#include "rpn.h"

#include <stdlib.h>
#include <string.h>

// Приоритет операторов
int get_precedence(const char *op) {
    if (strcmp(op, "^") == 0) return 4;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) return 3;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 2;
    return 0;
}

RPNExpression *shunting_yard(Lexer *lexer) {
    Stack *op_stack = stack_init();
    RPNExpression *output = malloc(sizeof(RPNExpression));
    output->tokens = malloc(sizeof(Token) * 256);  // Макс. 256 токенов
    output->size = 0;

    Token token;
    while ((token = lexer_next_token(lexer)).type != TOKEN_EOF) {
        if (token.type == TOKEN_ERROR) {
            rpn_free(output);
            stack_free(op_stack);
            return NULL;
        }

        if (token.type == TOKEN_NUMBER || token.type == TOKEN_VARIABLE) {
            output->tokens[output->size++] = token;
        } else if (token.type == TOKEN_FUNCTION) {
            stack_push(op_stack, token);
        } else if (token.type == TOKEN_OPERATOR) {
            while (!stack_is_empty(op_stack)) {
                Token top = stack_peek(op_stack);
                if (top.type == TOKEN_OPERATOR && get_precedence(top.value) >= get_precedence(token.value)) {
                    output->tokens[output->size++] = stack_pop(op_stack);
                } else
                    break;
            }
            stack_push(op_stack, token);
        } else if (token.type == TOKEN_LPAREN) {
            stack_push(op_stack, token);
        } else if (token.type == TOKEN_RPAREN) {
            while (!stack_is_empty(op_stack) && stack_peek(op_stack).type != TOKEN_LPAREN) {
                output->tokens[output->size++] = stack_pop(op_stack);
            }
            if (stack_is_empty(op_stack)) {
                rpn_free(output);
                stack_free(op_stack);
                return NULL;  // Несбалансированные скобки
            }
            stack_pop(op_stack);  // Удаляем '('
            if (!stack_is_empty(op_stack) && stack_peek(op_stack).type == TOKEN_FUNCTION) {
                output->tokens[output->size++] = stack_pop(op_stack);
            }
        }
    }

    // Выталкиваем оставшиеся операторы
    while (!stack_is_empty(op_stack)) {
        Token top = stack_pop(op_stack);
        if (top.type == TOKEN_LPAREN) {  // Несбалансированные скобки
            rpn_free(output);
            stack_free(op_stack);
            return NULL;
        }
        output->tokens[output->size++] = top;
    }

    stack_free(op_stack);
    return output;
}

void rpn_free(RPNExpression *expr) {
    free(expr->tokens);
    free(expr);
}