#include "headers/token.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Token *tokenize(const char *expression, int *num_tokens) {
      const char *current  = expression;
      int         capacity = 20;
      *num_tokens          = 0;

      // Allocate memory for an initial token array
      struct Token *tokens = malloc(capacity * sizeof(struct Token));
      if (!tokens) {
            perror("Failed to allocate memory for tokens");
            exit(EXIT_FAILURE);
      }

      // Lex tokens and store them in the array
      while (1) {
            struct Token token = lexer(&current);

            if (*num_tokens >= capacity) {
                  capacity *= 2;
                  struct Token *new_tokens = realloc(tokens, capacity * sizeof(struct Token));
                  if (!new_tokens) {
                        free_tokens(tokens, *num_tokens);
                        perror("Failed to reallocate memory for tokens");
                        exit(EXIT_FAILURE);
                  }
                  tokens = new_tokens;
            }

            tokens[*num_tokens] = token;
            (*num_tokens)++;

            if (token.type == END) {
                  break;
            }
      }

      return tokens;
}

struct Token lexer(const char **input) {
      while (isspace(**input)) {
            (*input)++;
      }

      // End of input
      if (**input == '\0') {
            return create_token(END, "");
      }

      // Handle numbers (sequences of digits)
      if (isdigit(**input)) {
            const char *start = *input;
            while (isdigit(**input)) {
                  (*input)++;
            }
            // Create a temporary buffer for the number
            int   length = *input - start;
            char *num    = malloc(length + 1);
            strncpy(num, start, length);
            num[length] = '\0';

            struct Token token = create_token(NUMBER, num);
            free(num); // Free temporary buffer
            return token;
      }

      char operator[2] = { 0, 0 };
      operator[0]      = ** input;

      switch (**input) {
      case '+':
            (*input)++;
            return create_token(PLUS, operator);
      case '-':
            (*input)++;
            return create_token(MINUS, operator);
      case '*':
            (*input)++;
            return create_token(MUL, operator);
      case '/':
            (*input)++;
            return create_token(DIV, operator);
      case '(':
            (*input)++;
            return create_token(LPAREN, operator);
      case ')':
            (*input)++;
            return create_token(RPAREN, operator);
      default:
            return create_token(END, "");
      }
      return create_token(END, "");
}

struct Token create_token(enum TokenType type, const char *value) {
      struct Token token;
      token.type = type;
      // Allocate new memory and copy the value
      token.value = strdup(value); // dynamically allocated so we have to free later
      return token;
}

void free_tokens(struct Token *tokens, int num_tokens) {
      for (int i = 0; i < num_tokens; i++) {
            if (tokens[i].value) {
                  free(tokens[i].value);
            }
      }
      free(tokens);
}

char *join_arguments(int argc, char *argv[]) {
      // Calculate the total length needed
      int total_length = 0;

      // e.g  [ ["2"], ["+"], ["50"]  ]
      for (int i = 1; i < argc; i++) {
            total_length += strlen(argv[i]) + 1;
      }

      // Allocate memory for the joined string
      char *joined = malloc(total_length); // +1 for null terminator
      if (!joined) {
            perror("malloc failed in join arguments");
            exit(1);
      }

      // Join the arguments
      joined[0] = '\0'; // Start with an empty string
      for (int i = 1; i < argc; i++) {
            strcat(joined, argv[i]); // Append the argument
            if (i < argc - 1) {
                  strcat(joined, " "); // Append a space if it's not the last argument
            }
      }

      return joined;
}
