#include <stdio.h>
#include "vm.h"

int main(int argc, char **argv)
{
	/* program 1 (main at 19) */
	const int dec = 0;
	int program[] = {
		/* simple decrement procedure */
		OP_LOAD, -3,
		OP_CONST, 0,
		OP_EQ,
		OP_JMPF, 10,
		OP_CONST, 0,
		OP_RET,
		OP_LOAD, -3,
		OP_CONST, 1,
		OP_SUB,
		OP_CALL, dec, 1,
		OP_RET,
		/* entrypoint */
		OP_CONST, 6,
		OP_CALL, dec, 1,
		OP_PRINT,
		OP_HALT
	};
	VM *vm;
	
	vm = VM_create(program, 19, 0);
	VM_run(vm);
	VM_delete(vm);
	return 0;
}
