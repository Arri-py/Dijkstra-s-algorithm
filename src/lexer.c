#include "lexer.h"
#include <ctype.h>
#include <string.h>

Lexer* lexer_init(const char *input) {
    Lexer *lexer = malloc(sizeof(Lexer));
    lexer->input = input;
    lexer->pos = 0;
    return lexer;
}

Token lexer_next_token(Lexer *lexer) {
    Token token = {TOKEN_ERROR, ""};
    char current;

    // Пропускаем пробелы
    while ((current = lexer->input[lexer->pos]) == ' ') lexer->pos++;

    // Конец строки
    if (current == '\0') {
        token.type = TOKEN_EOF;
        return token;
    }

    // Числа (например, 123 или 1.23)
    if (isdigit(current) || current == '.') {
        int i = 0;
        while (isdigit(lexer->input[lexer->pos]) || lexer->input[lexer->pos] == '.') {
            token.value[i++] = lexer->input[lexer->pos++];
        }
        token.value[i] = '\0';
        token.type = TOKEN_NUMBER;
        return token;
    }

    // Переменная (только 'x' в этой задаче)
    if (current == 'x') {
        token.value[0] = 'x';
        token.value[1] = '\0';
        token.type = TOKEN_VARIABLE;
        lexer->pos++;
        return token;
    }

    // Функции (sin, cos, tan, sqrt и т.д.)
    if (isalpha(current)) {
        int i = 0;
        while (isalpha(lexer->input[lexer->pos])) {
            token.value[i++] = lexer->input[lexer->pos++];
        }
        token.value[i] = '\0';
        token.type = TOKEN_FUNCTION;
        return token;
    }

    // Операторы (+ - * / ^)
    if (strchr("+-*/^", current)) {
        token.value[0] = current;
        token.value[1] = '\0';
        token.type = TOKEN_OPERATOR;
        lexer->pos++;
        return token;
    }

    // Скобки
    if (current == '(') {
        token.value[0] = '(';
        token.value[1] = '\0';
        token.type = TOKEN_LPAREN;
        lexer->pos++;
        return token;
    }
    if (current == ')') {
        token.value[0] = ')';
        token.value[1] = '\0';
        token.type = TOKEN_RPAREN;
        lexer->pos++;
        return token;
    }

    // Неизвестный символ → ошибка
    token.value[0] = current;
    token.value[1] = '\0';
    token.type = TOKEN_ERROR;
    lexer->pos++;
    return token;
}

void lexer_free(Lexer *lexer) {
    free(lexer);
}