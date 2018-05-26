#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* get_count:  returns total amount of objects */
int get_count(ast *obj)
{
	static int count = 0;

	if (obj == NULL)
		return count;
	get_count(obj->op.binary.left);
	get_count(obj->op.binary.right);
	++count;
}

/* get_op:  returns n-th operator from AST object */
char *get_op(ast *obj)
{
	if (obj == NULL)
		return NULL;
	return obj->op.binary.op;
}	

main()
{
	ast *obj;
	int i;

	obj = make_binaryExp("*", make_binaryExp("-", make_integerExp(5), make_integerExp(1)),
		make_integerExp(2));

	printf("(%d%s%d)%s%d = %d\n", obj->op.binary.left->op.binary.left->op.integer,
		obj->op.binary.left->op.binary.op,
		obj->op.binary.left->op.binary.right->op.integer,
		obj->op.binary.op, obj->op.binary.right->op.integer,
		(obj->op.binary.left->op.binary.left->op.integer-
		obj->op.binary.left->op.binary.right->op.integer)*
		obj->op.binary.right->op.integer);

	printf("Count of AST objects: %d\n", get_count(obj));
	printf("Operators: %s, %s\n", get_op(obj), get_op(obj->op.binary.left));
	free_ast(obj);
	return 0;
}
