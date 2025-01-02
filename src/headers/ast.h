#pragma once

#include <stdlib.h>

// Define the AST node types
typedef enum {
      AST_NUMBER,    // For numbers (e.g., 42, 3.14)
      AST_BINARY_OP, // For binary operators (e.g., +, -, *, /)
      AST_UNARY_OP,  // For unary operators (e.g., -42, +5)
      AST_GROUPING   // For grouped expressions (e.g., inside parentheses)
} ASTNodeType;

// Forward declaration of ASTNode
typedef struct ASTNode ASTNode;

// Define the AST node structure
struct ASTNode {
      ASTNodeType type; // The type of the node

      union {
            struct { // For AST_NUMBER
                  double value;
            } number;

            struct { // For AST_BINARY_OP
                  char     op;
                  ASTNode *left;
                  ASTNode *right;
            } binary;

            struct { // For AST_UNARY_OP
                  char     op;
                  ASTNode *operand;
            } unary;

            struct { // For AST_GROUPING
                  ASTNode *expression;
            } grouping;
      };
};

// Function prototypes for creating AST nodes
ASTNode *create_number_node(double value);
ASTNode *create_binary_node(char op, ASTNode *left, ASTNode *right);
ASTNode *create_unary_node(char op, ASTNode *operand);
ASTNode *create_grouping_node(ASTNode *expression);

// function to display/print the AST
void print_ast(ASTNode *node);

// Function prototype for freeing the AST
void free_ast(ASTNode *node);

