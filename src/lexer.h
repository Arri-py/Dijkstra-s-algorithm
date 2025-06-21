#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_VARIABLE,
    TOKEN_OPERATOR,
    TOKEN_FUNCTION,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    char value[32]; // Для хранения числа, имени функции и т.д.
} Token;

typedef struct {
    const char *input;
    int pos;
} Lexer;

Lexer* lexer_init(const char *input);
Token lexer_next_token(Lexer *lexer);
void lexer_free(Lexer *lexer);

#endif