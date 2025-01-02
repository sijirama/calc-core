#include "../headers/ast.h"
#include "utest.h"

UTEST(AST, CreateNumberNode) {
      ASTNode *node = create_number_node(42);

      ASSERT_NE(node, NULL);
      ASSERT_EQ((int)node->type, AST_NUMBER);
      ASSERT_EQ(node->number.value, 42);

      free_ast(node);
}

UTEST(AST, SimpleBinaryExpression) {
      ASTNode *left  = create_number_node(2);
      ASTNode *right = create_number_node(3);
      ASTNode *root  = create_binary_node('+', left, right);

      ASSERT_NE(root, NULL);
      ASSERT_EQ((int)root->type, AST_BINARY_OP);
      ASSERT_EQ(root->binary.op, '+');
      ASSERT_EQ(root->binary.left->number.value, 2);
      ASSERT_EQ(root->binary.right->number.value, 3);

      free_ast(root);
}

UTEST(AST, SimpleUnaryExpression) {
      ASTNode *right = create_number_node(3);
      ASTNode *root  = create_unary_node('+', right);

      ASSERT_NE(root, NULL);
      ASSERT_EQ((int)root->type, AST_UNARY_OP);
      ASSERT_EQ(root->unary.op, '+');
      ASSERT_EQ(root->unary.operand->number.value, 3);

      free_ast(root);
}
