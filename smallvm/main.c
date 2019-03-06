#include <stdio.h>
#include "vm.h"

int main(int argc, char **argv)
{
	/* program 1 (main at 19) */
	const int dec = 0;
	int program[] = {
		/* simple decrement procedure */
		OP_LOAD,
		OP_CONST, 0,
		OP_EQ,
		OP_JMPF, 8,
		OP_RET,
		OP_STORE,
		OP_SUB, 1,
		OP_PRINT,
		OP_JMP, dec,
		/* entrypoint */
		OP_CONST, 6,
		OP_CALL, dec, 1,
		OP_PRINT,
		OP_HALT
	};
	VM *vm;
	
	vm = VM_create(program, 14, 0);
	VM_run(vm);
	VM_delete(vm);
	return 0;
}
