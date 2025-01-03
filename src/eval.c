#include "headers/eval.h"
#include <math.h>
#include <stdio.h>

void print_result(double result) {
      if (fmod(result, 1.0) == 0.0) {
            // No fractional part, print as integer
            printf("%d\n", (int)result);
      } else {
            // Fractional part exists, print as float with two decimal places
            printf("%.2f\n", result);
      }
}

ASTNode *evaluate(ASTNode *node) {
      if (!node)
            return NULL;

      switch (node->type) {
      case AST_NUMBER:
            return node;
      case AST_UNARY_OP: {
            ASTNode *operand = evaluate(node->unary.operand);
            if (operand->type == AST_NUMBER) {
                  double result = (node->unary.op == '-') ? -operand->number.value : operand->number.value;
                  // free_ast(node);                    // Clean up old nodes
                  return create_number_node(result); // Return simplified node
            }
            node->unary.operand = operand; // Keep subtree for further evaluation
            return node;
      }
      case AST_BINARY_OP: {
            ASTNode *left  = evaluate(node->binary.left);
            ASTNode *right = evaluate(node->binary.right);

            if (left->type == AST_NUMBER && right->type == AST_NUMBER) {
                  double result;
                  switch (node->binary.op) {
                  case '+':
                        result = left->number.value + right->number.value;
                        break;
                  case '-':
                        result = left->number.value - right->number.value;
                        break;
                  case '*':
                        result = left->number.value * right->number.value;
                        break;
                  case '/':
                        if (fabs(right->number.value) < 1e-9) {
                              fprintf(stderr, "Error: Division by zero\n");
                              exit(EXIT_FAILURE);
                        }
                        result = left->number.value / right->number.value;
                        break;
                  default:
                        fprintf(stderr, "Error: Unknown operator '%c'\n", node->binary.op);
                        exit(EXIT_FAILURE);
                  }
                  // free_ast(node);                    // Clean up old nodes
                  return create_number_node(result); // Return simplified node
            }

            // If not reducible, preserve structure
            node->binary.left  = left;
            node->binary.right = right;
            return node;
      }
      default:
            fprintf(stderr, "Error: Unknown AST node type\n");
            exit(EXIT_FAILURE);
      }

      // TODO: Implement evaluation logic
      return NULL;
}
