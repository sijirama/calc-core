
#include "../headers/parser.h"
#include "../headers/token.h"
#include "utest.h"

UTEST(Parser, ParserPcedenceLevel) {
      char         *expression = "+ - / * (";
      int           num_tokens;
      struct Token *tokens = tokenize(expression, &num_tokens);

      ASSERT_EQ(get_precedence_level(tokens[0].type), 1);
      ASSERT_EQ(get_precedence_level(tokens[1].type), 1);
      ASSERT_EQ(get_precedence_level(tokens[2].type), 2);
      ASSERT_EQ(get_precedence_level(tokens[3].type), 2);
      ASSERT_EQ(get_precedence_level(tokens[num_tokens - 1].type), 0);

      free_tokens(tokens, num_tokens);
}
