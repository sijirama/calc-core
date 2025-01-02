#include <stdio.h>
#include <stdlib.h>
#include "headers/ast.h"
#include "headers/eval.h"
#include "headers/parser.h"
#include "headers/token.h"

int main(int argc, char *argv[]) {

      if (argc < 2) {
            printf("Usage: %s [app_mode]\n", argv[0]);
            return 1; // Exit with error code 1 (non-zero) if no app_mode
                      // provided. 0 indicates success.
      }

      // get the expression to loop
      char *expression = join_arguments(argc, argv);
      printf("Parsing Expression: %s\n", expression);

      int num_tokens;

      struct Token *tokens = tokenize(expression, &num_tokens);

      ASTNode *ast    = parse_program(tokens, num_tokens);
      ASTNode *result = evaluate(ast);

      print_result(result->number.value);

      free_ast(ast);
      free_tokens(tokens, num_tokens);
      free(expression);

      return 0;
}
