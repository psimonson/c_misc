#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* get_count:  returns total amount of objects */
int get_count(ast *obj)
{
	static int count = 0;

	if (!obj)
		return count;
	get_count(obj->op.binary.left);
	get_count(obj->op.binary.right);
	++count;
}

char *get_op(ast *obj)
{
	if (!obj)
		return NULL;
	return obj->op.binary.op;
}

char **get_ops(ast *obj, int size)
{
	char **ops = NULL;
	ast *astp;
	int i;

	ops = (char**)malloc(sizeof(char*)*(size+1));
	if (!ops)
		return NULL;

	i = 0;
	astp = obj;
	while (i < size) {
		if (astp->tag == binary_exp)
			ops[i++] = astp->op.binary.op;
		if (astp->op.binary.left != NULL)
			astp = astp->op.binary.left;
		else
			astp = astp->op.binary.right;
	}
	ops[i] = NULL;
	return ops;
}

int get_op_count(ast *obj)
{
	static int count = 0;

	if (!obj)
		return count;
	get_op_count(obj->op.binary.left);
	get_op_count(obj->op.binary.right);
	if (obj->tag == binary_exp)
		++count;
}

int main()
{
	char **ops;
	ast *obj;
	int i, count;

	obj = make_binaryExp("*", make_binaryExp("-", make_integerExp(5), make_integerExp(1)),
		make_integerExp(2));
	if (!obj)
		return 1;

	count = get_op_count(obj);
	ops = get_ops(obj, count);
	for (i = 0; i < count; i++)	
		printf("%d: %s\n", i+1, ops[i]);
/*	printf("%d: %s %s\n", count, get_op(obj), get_op(obj->op.binary.left)); */
	free_ast(obj);
	return 0;
}
