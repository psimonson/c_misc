#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ast *make_binaryExp(char *operator, ast *left, ast *right)
{
	ast *new_ast = (ast*)malloc(sizeof(*new_ast));
	if (new_ast) {
		new_ast->tag = binary_exp;
		strcpy(new_ast->op.binary.op, operator);
		new_ast->op.binary.left = left;
		new_ast->op.binary.right = right;
		return new_ast;
	} else
		fprintf(stderr, "Error: cannot create AST.\n");
	return NULL;
}

ast *make_integerExp(int n)
{
	ast *new_ast = (ast*)malloc(sizeof(*new_ast));
	if (new_ast) {
		new_ast->tag = integer_exp;
		new_ast->op.integer = n;
		return new_ast;
	} else
		fprintf(stderr, "Error: cannot create AST.\n");
	return NULL;
}

/*
ast *make_stringExp(char *operator)
{
	ast *new_ast = (ast*)malloc(sizeof(*new_ast));
	if (new_ast) {
		new_ast->tag = string_exp;
		new_ast->op.string = strdup(operator);
		return new_ast;
	} else
		fprintf(stderr, "Error: cannot create AST.\n");
	return NULL;
}
*/

void free_ast(ast *p)
{
	if (p) {
		free_ast(p->op.binary.left);
		free_ast(p->op.binary.right);
		free(p);
	}
}
