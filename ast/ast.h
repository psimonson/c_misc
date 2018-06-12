#ifndef PRS_AST_H
#define PRS_AST_H

#define MAXOPLEN 64

typedef struct Exp {
	enum { integer_exp, string_exp, binary_exp, variable_exp } tag;
	union {
		int integer;
		struct {
			char op[MAXOPLEN];
			struct Exp *left;
			struct Exp *right;
		} binary;
		struct {
			char op[MAXOPLEN];
			struct Exp *left;
			struct Exp *right;
		} variable;
	} op;
} ast;

ast *make_binaryExp(char *, ast *, ast *);
ast *make_integerExp(int);
void free_ast(ast *p);

#endif
