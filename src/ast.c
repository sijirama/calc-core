#include "headers/ast.h"
#include <stdio.h>

// Create a number node
ASTNode *create_number_node(double value) {
      ASTNode *node      = malloc(sizeof(ASTNode));
      node->type         = AST_NUMBER;
      node->number.value = value;
      return node;
}

// Create a binary operator node
ASTNode *create_binary_node(char op, ASTNode *left, ASTNode *right) {
      ASTNode *node      = malloc(sizeof(ASTNode));
      node->type         = AST_BINARY_OP;
      node->binary.op    = op;
      node->binary.left  = left;
      node->binary.right = right;
      return node;
}

// Create a unary operator node
ASTNode *create_unary_node(char op, ASTNode *operand) {
      ASTNode *node       = malloc(sizeof(ASTNode));
      node->type          = AST_UNARY_OP;
      node->unary.op      = op;
      node->unary.operand = operand;
      return node;
}

// Create a grouping node
ASTNode *create_grouping_node(ASTNode *expression) {
      ASTNode *node             = malloc(sizeof(ASTNode));
      node->type                = AST_GROUPING;
      node->grouping.expression = expression;
      return node;
}

// Free the AST
void free_ast(ASTNode *node) {
      if (!node)
            return;

      switch (node->type) {
      case AST_BINARY_OP:
            free_ast(node->binary.left);
            free_ast(node->binary.right);
            break;
      case AST_UNARY_OP:
            free_ast(node->unary.operand);
            break;
      case AST_GROUPING:
            free_ast(node->grouping.expression);
            break;
      default:
            break; // AST_NUMBER doesn't have sub-nodes
      }

      free(node);
}

void print_ast(ASTNode *node) {
      if (!node)
            return; // If the node is NULL, do nothing

      switch (node->type) {
      case AST_NUMBER:
            printf("%f", node->number.value); // Print the number value
            break;

      case AST_BINARY_OP:
            // Print left operand, operator, and right operand in infix form
            printf("(");
            print_ast(node->binary.left);
            printf(" %c ", node->binary.op); // Print the operator
            print_ast(node->binary.right);
            printf(")");
            break;

      case AST_UNARY_OP:
            // Print the operator and operand for unary operations
            printf("(%c", node->unary.op);
            print_ast(node->unary.operand);
            printf(")");
            break;

      case AST_GROUPING:
            // Print the grouped expression inside parentheses
            printf("(");
            print_ast(node->grouping.expression);
            printf(")");
            break;

      default:
            printf("Unknown node type");
            break;
      }
}
