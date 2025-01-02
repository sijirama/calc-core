#pragma once

#include "ast.h"
#include "token.h"

int get_precedence_level(enum TokenType token);

ASTNode * parse_program(struct Token *tokens, int num_tokens);

ASTNode * parser_primary(struct Token **token);

ASTNode * parse_expression(struct Token **tokens, int precedence);


char get_operator_char(enum TokenType type);
