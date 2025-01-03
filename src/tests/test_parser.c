
#include <stdio.h>
#include "../headers/parser.h"
#include "../headers/token.h"
#include "utest.h"

UTEST(Parser, ParserPrecedenceLevel) {
      char         *expression = "+ - / * (";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);

      ASSERT_EQ(get_precedence_level(tokens[0].type), 1);
      ASSERT_EQ(get_precedence_level(tokens[1].type), 1);
      ASSERT_EQ(get_precedence_level(tokens[2].type), 2);
      ASSERT_EQ(get_precedence_level(tokens[3].type), 2);
      ASSERT_EQ(get_precedence_level(tokens[4].type), 3);
      ASSERT_EQ(get_precedence_level(tokens[num_tokens - 1].type), 0);

      free_tokens(tokens, num_tokens);
}

// Test: Simple number parsing
UTEST(Parser, SimpleNumber) {
      char         *expression = "42";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASSERT_EQ(ast->type, AST_NUMBER);
      ASSERT_EQ(ast->number.value, 42.0);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}

UTEST(Parser, UnaryNumber) {
      char         *expression = "-42";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASSERT_EQ(ast->type, AST_UNARY_OP);
      ASSERT_EQ(ast->unary.op, '-');                     // Check the unary operator
      ASSERT_EQ(ast->unary.operand->type, AST_NUMBER);   // Check that operand is a number node
      ASSERT_EQ(ast->unary.operand->number.value, 42.0); // Check the number value

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}

// Test: Simple addition
UTEST(Parser, SimpleAddition) {
      char         *expression = "2 + 3";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASSERT_EQ(ast->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.op, '+');
      ASSERT_EQ(ast->binary.left->type, AST_NUMBER);
      ASSERT_EQ(ast->binary.left->number.value, 2.0);
      ASSERT_EQ(ast->binary.right->type, AST_NUMBER);
      ASSERT_EQ(ast->binary.right->number.value, 3.0);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}

// Test: Operator precedence
UTEST(Parser, OperatorPrecedence) {
      char         *expression = "2 + 3 * 4";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASSERT_EQ(ast->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.op, '+');
      ASSERT_EQ(ast->binary.left->type, AST_NUMBER);
      ASSERT_EQ(ast->binary.left->number.value, 2.0);

      // Check right subtree (3 * 4)
      ASSERT_EQ(ast->binary.right->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.right->binary.op, '*');
      ASSERT_EQ(ast->binary.right->binary.left->number.value, 3.0);
      ASSERT_EQ(ast->binary.right->binary.right->number.value, 4.0);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}

// Test: Parentheses handling
UTEST(Parser, Parentheses) {
      char         *expression = "(2 + 3) * 4";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASSERT_EQ(ast->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.op, '*');

      // Check left subtree (2 + 3)
      ASSERT_EQ(ast->binary.left->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.left->binary.op, '+');
      ASSERT_EQ(ast->binary.left->binary.left->number.value, 2.0);
      ASSERT_EQ(ast->binary.left->binary.right->number.value, 3.0);

      // Check right number (4)
      ASSERT_EQ(ast->binary.right->type, AST_NUMBER);
      ASSERT_EQ(ast->binary.right->number.value, 4.0);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}

// Test: Complex expression
UTEST(Parser, ComplexExpression) {
      char         *expression = "1 + 2 * 3 - (4 / 2)";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASSERT_EQ(ast->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.op, '-');

      // Check left subtree (1 + 2 * 3)
      ASSERT_EQ(ast->binary.left->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.left->binary.op, '+');
      ASSERT_EQ(ast->binary.left->binary.left->number.value, 1.0);
      ASSERT_EQ(ast->binary.left->binary.right->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.left->binary.right->binary.op, '*');
      ASSERT_EQ(ast->binary.left->binary.right->binary.left->number.value, 2.0);
      ASSERT_EQ(ast->binary.left->binary.right->binary.right->number.value, 3.0);

      // Check right subtree (4 / 2)
      ASSERT_EQ(ast->binary.right->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.right->binary.op, '/');
      ASSERT_EQ(ast->binary.right->binary.left->number.value, 4.0);
      ASSERT_EQ(ast->binary.right->binary.right->number.value, 2.0);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}

// Test: Empty input
UTEST(Parser, EmptyInput) {
      char         *expression = "";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast == NULL);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}

// INFO: TESTS FROM CHATGPT

// Test: Nested parentheses
UTEST(Parser, NestedParentheses) {
      char         *expression = "((2 + 3) * 4)";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASSERT_EQ(ast->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.op, '*');
      ASSERT_EQ(ast->binary.left->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.left->binary.op, '+');
      ASSERT_EQ(ast->binary.left->binary.left->number.value, 2.0);
      ASSERT_EQ(ast->binary.left->binary.right->number.value, 3.0);
      ASSERT_EQ(ast->binary.right->type, AST_NUMBER);
      ASSERT_EQ(ast->binary.right->number.value, 4.0);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}

// Test: Decimal numbers
UTEST(Parser, DecimalNumbers) {
      char         *expression = "3.14 + 2.71";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASSERT_EQ(ast->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.op, '+');
      ASSERT_EQ(ast->binary.left->type, AST_NUMBER);
      ASSERT_EQ(ast->binary.left->number.value, 3.14);
      ASSERT_EQ(ast->binary.right->type, AST_NUMBER);
      ASSERT_EQ(ast->binary.right->number.value, 2.71);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}

// Test: Mixed unary and binary operators
UTEST(Parser, MixedUnaryBinaryOperators) {
      char         *expression = "-3 + 5";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASSERT_EQ(ast->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.op, '+');
      ASSERT_EQ(ast->binary.left->type, AST_UNARY_OP);
      ASSERT_EQ(ast->binary.left->unary.op, '-');
      ASSERT_EQ(ast->binary.left->unary.operand->number.value, 3.0);
      ASSERT_EQ(ast->binary.right->type, AST_NUMBER);
      ASSERT_EQ(ast->binary.right->number.value, 5.0);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}

// Test: Whitespace handling
UTEST(Parser, WhitespaceHandling) {
      char         *expression = "   1  +    2 ";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASSERT_EQ(ast->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.op, '+');
      ASSERT_EQ(ast->binary.left->type, AST_NUMBER);
      ASSERT_EQ(ast->binary.left->number.value, 1.0);
      ASSERT_EQ(ast->binary.right->type, AST_NUMBER);
      ASSERT_EQ(ast->binary.right->number.value, 2.0);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}

// Test: Large numbers
UTEST(Parser, LargeNumbers) {
      char         *expression = "999999999 + 1";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASSERT_EQ(ast->type, AST_BINARY_OP);
      ASSERT_EQ(ast->binary.op, '+');
      ASSERT_EQ(ast->binary.left->type, AST_NUMBER);
      ASSERT_EQ(ast->binary.left->number.value, 999999999.0);
      ASSERT_EQ(ast->binary.right->type, AST_NUMBER);
      ASSERT_EQ(ast->binary.right->number.value, 1.0);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}
