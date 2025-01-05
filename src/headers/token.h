#pragma once

enum TokenType {
      NUMBER,
      PLUS,
      MINUS,
      MUL,
      DIV,
      LPAREN,
      RPAREN,
      END, // To mark the end of the input
      POWER,
};

struct Token {
      enum TokenType type;
      char          *value;
};

struct Token *tokenize(const char *expression, int *num_tokens);
struct Token  lexer(const char **input);
struct Token  create_token(enum TokenType type, const char *value);
void          free_tokens(struct Token *tokens, int num_tokens);
char         *join_arguments(int argc, char *argv[]);
