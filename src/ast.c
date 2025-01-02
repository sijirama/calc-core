#include "headers/ast.h"

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
