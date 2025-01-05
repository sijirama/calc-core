#include "headers/parser.h"
#include <stdio.h>
#include "headers/ast.h"
#include "headers/token.h"

ASTNode *parse_program(struct Token *tokens, int num_tokens) {

      if (num_tokens == 0) {
            return NULL; // No tokens to parse
      }

      struct Token *current = tokens;
      return parse_expression(&current, 0);
}

ASTNode *parse_primary(struct Token **token) {

      if (!token) {
            return NULL;
      }

      switch ((*token)->type) {
      case MINUS: {
            *token += 1; // Consume the minus token
            ASTNode *operand = parse_primary(token);
            if (!operand) {
                  fprintf(stderr, "Error: Missing operand for unary minus\n");
                  exit(EXIT_FAILURE);
            }
            return create_unary_node('-', operand);
      }
      case NUMBER: {
            double value = atof((*token)->value);
            *token += 1; // Consume the number token
            return create_number_node(value);
      }
      case LPAREN: {
            // Parse a sub-expression inside parentheses
            *token += 1; // Advance past '('
            ASTNode *expr = parse_expression(token, 0);
            if (!expr) {
                  fprintf(stderr, "Error: Invalid expression inside parentheses\n");
                  exit(EXIT_FAILURE);
            }
            if ((*token)->type != RPAREN) {
                  fprintf(stderr, "Error: Expected closing parenthesis\n");
                  exit(EXIT_FAILURE);
            }
            *token += 1; // Advance past ')'
            return expr;
      }
      case END:
            return NULL;

      default:
            fprintf(stderr, "Error: Unexpected token in parse_primary, ");
            printf("Got ( %d  )\n\n", (*token)->type);
            exit(EXIT_FAILURE);
      }
}

int get_precedence_level(enum TokenType token) {
      if (!token) {
            return 0;
      }

      switch (token) {
      case PLUS:
      case MINUS:
            return 1;
      case MUL:
      case DIV:
            return 2;
      case LPAREN:
      case POWER:
            return 3;
      default:
            return 0;
      };

      return 0;
}

char get_operator_char(enum TokenType type) {
      switch (type) {
      case PLUS:
            return '+';
      case MINUS:
            return '-';
      case MUL:
            return '*';
      case DIV:
            return '/';
      case POWER:
            return '^';
      default:
            return '\0';
      }
}

ASTNode *parse_expression(struct Token **tokens, int precedence) {
      ASTNode *left = parse_primary(tokens);

      if (!left) {
            return NULL; // No more tokens to parse, so return the left operand as is
      }

      while (*tokens && get_precedence_level((*tokens)->type) > precedence) {
            enum TokenType op = (*tokens)->type;

            int next_precedence = get_precedence_level(op);

            *tokens += 1; // Advance past operator

            ASTNode *right = parse_expression(tokens, next_precedence);
            if (!right) {
                  fprintf(stderr, "Error: Missing right-hand side for operator\n");
                  exit(EXIT_FAILURE);
            }

            left = create_binary_node(get_operator_char(op), left, right);
      }

      return left;
}
