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

ASTNode *parse_primary(struct Token *token) {

      if (!token) {
            return NULL;
      }

      switch (token->type) {
      case NUMBER:
            return create_number_node((double)*token->value);
      case LPAREN:
            // Parse a sub-expression inside parentheses
            token += 1; // Advance past '('
            ASTNode *expr = parse_expression(&token, 0);
            if (token->type != RPAREN) {
                  fprintf(stderr, "Error: Expected closing parenthesis\n");
                  exit(EXIT_FAILURE);
            }
            token += 1; // Advance past ')'
            return expr;
      default:
            fprintf(stderr, "Error: Unexpected token in parse_primary\nGot: ");
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
            return 3;
      default:
            return 0;
      };

      return 0;
}

ASTNode *parse_expression(struct Token **tokens, int precedence) {
      ASTNode *left = parse_primary(*tokens);
      *tokens += 1; // Advance after primary;

      while (*tokens && get_precedence_level((*tokens)->type) > precedence) {
            enum TokenType op              = (*tokens)->type;
            int            next_precedence = get_precedence_level(op);
            *tokens += 1; // Advance past operator

            ASTNode *right = parse_expression(tokens, next_precedence);
            left           = create_binary_node(op, left, right); // Combine into AST
      }

      return left;
}
