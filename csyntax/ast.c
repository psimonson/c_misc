#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOPLEN 64

typedef struct {
	enum { integer_exp, binary_exp, variable_exp } tag;
	union {
		int integerExp;
		struct {
			char op[MAXOPLEN;
			ast *left;
			ast *right;
		} binaryExp;
		struct {
			char op[MAXOPLEN];
			ast *left;
			ast *right;
		} variableExp;
	} op;
} ast;

ast *make_binaryExp(char *operator, ast *left, ast *right)
{
	ast *new_ast = (ast*)malloc(sizeof(*new_ast));
	if (new_ast) {
		new_ast->tag = binary_exp;
		strcpy(new_ast->op.binaryExp.op, operator);
		new_ast->op.binaryExp.left = left;
		new_ast->op.binaryExp.right = right;
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
		new_ast->op.integerExp = n;
		return new_ast;
	} else
		fprintf(stderr, "Error: cannot create AST.\n");
	return NULL;
}

void free_ast(ast *p)
{
	if (p)
		free(p);
}
