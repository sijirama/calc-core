
#include <stdio.h>
#include "../headers/eval.h"
#include "../headers/parser.h"
#include "utest.h"

// Test: Simple number evaluation
UTEST(Evaluator, SimpleNumber) {
      char         *expression = "42";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASTNode *result = evaluate(ast);
      ASSERT_EQ(result->number.value, 42.0);

      free_ast(ast);
      // free_ast(result);
      free_tokens(tokens, num_tokens);
}

// Test: Simple addition
UTEST(Evaluator, SimpleAddition) {
      char         *expression = "2 + 3";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASTNode *result = evaluate(ast);
      ASSERT_EQ(result->number.value, 5.0);

      free_ast(ast);
      // free_ast(result);
      free_tokens(tokens, num_tokens);
}

/*UTEST(Evaluator, SimplePower) {*/
/*      char         *expression = "2 ^ 2";*/
/*      int           num_tokens;*/
/*      struct Token *tokens = tokenize(expression, &num_tokens);*/
/*      ASTNode      *ast    = parse_program(tokens, num_tokens);*/
/**/
/*      ASSERT_TRUE(ast != NULL);*/
/*      ASTNode *result = evaluate(ast);*/
/*      ASSERT_EQ(result->number.value, 4.0);*/
/**/
/*      free_ast(ast);*/
/*      // free_ast(result);*/
/*      free_tokens(tokens, num_tokens);*/
/*}*/

// Test: Simple subtraction
UTEST(Evaluator, SimpleSubtraction) {
      char         *expression = "5 - 3";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASTNode *result = evaluate(ast);
      ASSERT_EQ(result->number.value, 2.0);

      free_ast(ast);
      // free_ast(result);
      free_tokens(tokens, num_tokens);
}

// Test: Simple multiplication
UTEST(Evaluator, SimpleMultiplication) {
      char         *expression = "4 * 3";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASTNode *result = evaluate(ast);
      ASSERT_EQ(result->number.value, 12.0);

      free_ast(ast);
      // free_ast(result);
      free_tokens(tokens, num_tokens);
}

// Test: Simple division
UTEST(Evaluator, SimpleDivision) {
      char         *expression = "8 / 2";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASTNode *result = evaluate(ast);
      ASSERT_EQ(result->number.value, 4.0);

      free_ast(ast);
      // free_ast(result);
      free_tokens(tokens, num_tokens);
}

// TODO: Test: Division by zero (should handle error)
/*UTEST(Evaluator, DivisionByZero) {*/
/*      char         *expression = "8 / 0";*/
/*      int           num_tokens;*/
/*      struct Token *tokens = tokenize(expression, &num_tokens);*/
/*      ASTNode      *ast    = parse_program(tokens, num_tokens);*/
/**/
/*      ASSERT_TRUE(ast != NULL);*/
/*      ASTNode *result = evaluate(ast);*/
/*      // Assuming your evaluator handles division by zero gracefully*/
/*      ASSERT_EQ(result->number.value, INFINITY); // or some other appropriate value like NAN*/
/**/
/*      free_ast(ast);free_ast(result);*/
/*      free_tokens(tokens, num_tokens);*/
/*}*/

// Test: Operator precedence (multiplication before addition)
UTEST(Evaluator, OperatorPrecedence) {
      char         *expression = "2 + 3 * 4";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASTNode *result = evaluate(ast);
      ASSERT_EQ(result->number.value, 14.0); // Multiplication before addition (3 * 4 = 12, then 2 + 12 = 14)

      free_ast(ast);
      // free_ast(result);
      free_tokens(tokens, num_tokens);
}

// Test: Parentheses (to override operator precedence)
UTEST(Evaluator, Parentheses) {
      char         *expression = "(2 + 3) * 4";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASTNode *result = evaluate(ast);
      ASSERT_EQ(result->number.value, 20.0); // Parentheses override multiplication precedence (2 + 3 = 5, then 5 * 4 = 20)

      free_ast(ast);
      // free_ast(result);
      free_tokens(tokens, num_tokens);
}

// Test: Complex expression with multiple operators
UTEST(Evaluator, ComplexExpression) {
      char         *expression = "1 + 2 * 3 - (4 / 2)";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASTNode *result = evaluate(ast);
      ASSERT_EQ(result->number.value, 5.0); // 1 + (2 * 3) - (4 / 2) = 1 + 6 - 2 = 5

      free_ast(ast);
      // free_ast(result);
      free_tokens(tokens, num_tokens);
}

// Test: Unary operation (negative number)
UTEST(Evaluator, UnaryMinus) {
      char         *expression = "-42";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASTNode *result = evaluate(ast);
      ASSERT_EQ(result->number.value, -42.0);

      free_ast(ast);
      // free_ast(result);
      free_tokens(tokens, num_tokens);
}

// Test: Nested expressions with unary and binary operators
UTEST(Evaluator, NestedUnaryAndBinary) {
      char         *expression = "-(2 + 3) * 4";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASTNode *result = evaluate(ast);
      ASSERT_EQ(result->number.value, -20.0); // -(2 + 3) * 4 = -5 * 4 = -20

      free_ast(ast);
      // free_ast(result);
      free_tokens(tokens, num_tokens);
}

// Test: Multiple parentheses for grouping
UTEST(Evaluator, MultipleParentheses) {
      char         *expression = "((2 + 3) * 4) + (5 * 6)";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASTNode *result = evaluate(ast);
      ASSERT_EQ(result->number.value, 50.0); // ((2 + 3) * 4) + (5 * 6) = (5 * 4) + (5 * 6) = 20 + 30 = 50

      free_ast(ast);
      // free_ast(result);
      free_tokens(tokens, num_tokens);
}

// Test: No expression (empty input)
UTEST(Evaluator, EmptyInput) {
      char         *expression = "";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast == NULL);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}

// Test: Floating-point division
/*UTEST(Evaluator, FloatingPointDivision) {*/
/*      char         *expression = "7 / 3";*/
/*      int           num_tokens;*/
/*      struct Token *tokens = tokenize(expression, &num_tokens);*/
/*      ASTNode      *ast    = parse_program(tokens, num_tokens);*/
/**/
/*      ASSERT_TRUE(ast != NULL);*/
/*      ASTNode *result = evaluate(ast);*/
/*      ASSERT_EQ(result->number.value, 2.333333); // 7 / 3 = 2.333333...*/
/**/
/*      free_ast(ast);*/
/*      // free_ast(result);*/
/*      free_tokens(tokens, num_tokens);*/
/*}*/

/*
The failure happens because floating-point numbers are inherently imprecise in computing. Even though 2.333333 looks identical to
what you're comparing, it might have tiny differences due to the way floating-point arithmetic works.

To fix this, you should compare floating-point numbers within a small tolerance (epsilon), rather than checking for exact
equality. Here's how you can modify the test:

Why It Works

- fabs (absolute value) ensures we are looking at the magnitude of the difference.
- The epsilon value (1e-6) determines the precision tolerance. If the difference between the actual result and expected value is
less than this, they are considered equal.

This should resolve the test failure. Let me know how it goes!
*/

UTEST(Evaluator, FloatingPointDivision2) {
      char         *expression = "7 / 3";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);
      ASTNode      *ast    = parse_program(tokens, num_tokens);

      ASSERT_TRUE(ast != NULL);
      ASTNode *result = evaluate(ast);

      double expected = 7.0 / 3.0;
      double epsilon  = 1e-6; // Tolerance for floating-point comparison

      ASSERT_TRUE(fabs(result->number.value - expected) < epsilon); // Compare within tolerance

      free_ast(ast);
      free_tokens(tokens, num_tokens);
}
