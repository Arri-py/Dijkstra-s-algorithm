#include "lexer.h"

#include <stdlib.h>
#include <string.h>

#include "myctype.h"

static Token create_token(TokenType type, const char *value) {
    Token token = {type, ""};
    strncpy(token.value, value, sizeof(token.value) - 1);
    token.value[sizeof(token.value) - 1] = '\0';
    return token;
}

static Token handle_number(Lexer *lexer) {
    char buffer[32] = {0};
    size_t i = 0;

    while (my_isdigit(lexer->input[lexer->pos])) {
        if (i < sizeof(buffer) - 1) {
            buffer[i++] = lexer->input[lexer->pos++];
        } else {
            lexer->pos++;
        }
    }

    if (lexer->input[lexer->pos] == '.') {
        if (i < sizeof(buffer) - 1) {
            buffer[i++] = lexer->input[lexer->pos++];
        } else {
            lexer->pos++;
        }

        while (my_isdigit(lexer->input[lexer->pos])) {
            if (i < sizeof(buffer) - 1) {
                buffer[i++] = lexer->input[lexer->pos++];
            } else {
                lexer->pos++;
            }
        }
    }
    return create_token(TOKEN_NUMBER, buffer);
}

static Token handle_function(Lexer *lexer) {
    char buffer[32] = {0};
    size_t i = 0;

    while (my_isalpha(lexer->input[lexer->pos])) {
        if (i < sizeof(buffer) - 1) {
            buffer[i++] = lexer->input[lexer->pos++];
        } else {
            lexer->pos++;
        }
    }

    return create_token(TOKEN_FUNCTION, buffer);
}

Lexer *lexer_init(const char *input) {
    Lexer *lexer = malloc(sizeof(Lexer));
    if (!lexer) return NULL;
    lexer->input = input;
    lexer->pos = 0;
    return lexer;
}

Token lexer_next_token(Lexer *lexer) {
    while (lexer->input[lexer->pos] == ' ') {
        lexer->pos++;
    }
    char current = lexer->input[lexer->pos];
    if (current == '\0') {
        return create_token(TOKEN_EOF, "");
    }

    switch (current) {
        case 'x':
            lexer->pos++;
            return create_token(TOKEN_VARIABLE, "x");
        case '(':
            lexer->pos++;
            return create_token(TOKEN_LPAREN, "(");
        case ')':
            lexer->pos++;
            return create_token(TOKEN_RPAREN, ")");
        case '+':
        case '-':
        case '*':
        case '/':
        case '^': {
            char op[2] = {current, '\0'};
            lexer->pos++;
            return create_token(TOKEN_OPERATOR, op);
        }
    }

    if (my_isdigit(current)) {
        return handle_number(lexer);
    }
    if (my_isalpha(current)) {
        return handle_function(lexer);
    }

    char error[2] = {current, '\0'};
    lexer->pos++;
    return create_token(TOKEN_ERROR, error);
}

void lexer_free(Lexer *lexer) { free(lexer); }