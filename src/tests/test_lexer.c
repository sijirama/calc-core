#include "../headers/token.h" // Your tokenizer header file
#include "utest.h"

// Test: Tokenizing a simple expression
UTEST(Lexer, SimpleExpression) {
      char         *expression = "2 + 3";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);

      ASSERT_EQ(num_tokens, 4);

      ASSERT_EQ((int)tokens[0].type, NUMBER);
      ASSERT_STREQ(tokens[0].value, "2");

      ASSERT_EQ((int)tokens[1].type, PLUS);
      ASSERT_STREQ(tokens[1].value, "+");

      ASSERT_EQ((int)tokens[2].type, NUMBER);
      ASSERT_STREQ(tokens[2].value, "3");

      ASSERT_EQ((int)tokens[3].type, END);

      free_tokens(tokens, num_tokens);
}

// Test: Handling empty input
UTEST(Lexer, EmptyInput) {
      char         *expression = "";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);

      ASSERT_EQ(num_tokens, 1);
      ASSERT_EQ((int)tokens[0].type, END);

      free_tokens(tokens, num_tokens);
}

// Test: Tokenizing complex expression
UTEST(Lexer, ComplexExpression) {
      char         *expression = "12 + 34 * (56 - 78) / 90";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);

      ASSERT_EQ((int)tokens[0].type, NUMBER);
      ASSERT_STREQ(tokens[0].value, "12");

      ASSERT_EQ((int)tokens[1].type, PLUS);
      ASSERT_EQ((int)tokens[2].type, NUMBER);
      ASSERT_STREQ(tokens[2].value, "34");

      ASSERT_EQ((int)tokens[3].type, MUL);
      ASSERT_EQ((int)tokens[4].type, LPAREN);
      ASSERT_EQ((int)tokens[5].type, NUMBER);
      ASSERT_STREQ(tokens[5].value, "56");

      ASSERT_EQ((int)tokens[6].type, MINUS);
      ASSERT_EQ((int)tokens[7].type, NUMBER);
      ASSERT_STREQ(tokens[7].value, "78");

      ASSERT_EQ((int)tokens[8].type, RPAREN);
      ASSERT_EQ((int)tokens[9].type, DIV);
      ASSERT_EQ((int)tokens[10].type, NUMBER);
      ASSERT_STREQ(tokens[10].value, "90");

      ASSERT_EQ((int)tokens[11].type, END);

      free_tokens(tokens, num_tokens);
}

// Test: Unary operators
UTEST(Lexer, UnaryOperators) {
      char         *expression = "-42 + +3";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);

      ASSERT_EQ((int)tokens[0].type, MINUS);
      ASSERT_EQ((int)tokens[1].type, NUMBER);
      ASSERT_STREQ(tokens[1].value, "42");

      ASSERT_EQ((int)tokens[2].type, PLUS);
      ASSERT_EQ((int)tokens[3].type, PLUS);
      ASSERT_EQ((int)tokens[4].type, NUMBER);
      ASSERT_STREQ(tokens[4].value, "3");

      ASSERT_EQ((int)tokens[5].type, END);

      free_tokens(tokens, num_tokens);
}

// Test: Whitespace handling
UTEST(Lexer, WhitespaceHandling) {
      char         *expression = "  2\t+\n3 ";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);

      ASSERT_EQ((int)tokens[0].type, NUMBER);
      ASSERT_STREQ(tokens[0].value, "2");

      ASSERT_EQ((int)tokens[1].type, PLUS);
      ASSERT_EQ((int)tokens[2].type, NUMBER);
      ASSERT_STREQ(tokens[2].value, "3");

      ASSERT_EQ((int)tokens[3].type, END);

      free_tokens(tokens, num_tokens);
}

// Test: Floating-point numbers
UTEST(Lexer, FloatingPointNumbers) {
      char         *expression = "3.14 + 2.71";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);

      ASSERT_EQ((int)tokens[0].type, NUMBER);
      ASSERT_STREQ(tokens[0].value, "3.14");

      ASSERT_EQ((int)tokens[1].type, PLUS);
      ASSERT_EQ((int)tokens[2].type, NUMBER);
      ASSERT_STREQ(tokens[2].value, "2.71");

      ASSERT_EQ((int)tokens[3].type, END);

      free_tokens(tokens, num_tokens);
}

// Test: Long expressions
UTEST(Lexer, LongExpression) {
      char         *expression = "1 + 2 - 3 * 4 / 5 + (6 - 7 * 8)";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);

      ASSERT_GT(num_tokens, 0); // Ensure there are tokens
      ASSERT_EQ((int)tokens[num_tokens - 1].type, END);

      free_tokens(tokens, num_tokens);
}

// Test: Nested parentheses
UTEST(Lexer, NestedParentheses) {
      char         *expression = "((1 + 2) * (3 / 4))";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);

      ASSERT_EQ((int)tokens[0].type, LPAREN);
      ASSERT_EQ((int)tokens[1].type, LPAREN);
      ASSERT_EQ((int)tokens[2].type, NUMBER);
      ASSERT_STREQ(tokens[2].value, "1");

      ASSERT_EQ((int)tokens[3].type, PLUS);
      ASSERT_EQ((int)tokens[4].type, NUMBER);
      ASSERT_STREQ(tokens[4].value, "2");

      ASSERT_EQ((int)tokens[5].type, RPAREN);
      ASSERT_EQ((int)tokens[6].type, MUL);
      ASSERT_EQ((int)tokens[7].type, LPAREN);

      ASSERT_EQ((int)tokens[8].type, NUMBER);
      ASSERT_STREQ(tokens[8].value, "3");

      ASSERT_EQ((int)tokens[9].type, DIV);
      ASSERT_EQ((int)tokens[10].type, NUMBER);
      ASSERT_STREQ(tokens[10].value, "4");

      ASSERT_EQ((int)tokens[11].type, RPAREN);
      ASSERT_EQ((int)tokens[12].type, RPAREN);

      ASSERT_EQ((int)tokens[13].type, END);

      free_tokens(tokens, num_tokens);
}

UTEST_MAIN();
