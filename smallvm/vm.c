#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

/* VM_create:  creates a new VM object */
VM* VM_create(int *code, int pc, int datasize)
{
	VM* vm = (VM*)malloc(sizeof(VM));
	if (!vm)
		return NULL;
	vm->code = code;
	vm->pc = pc;
	vm->fp = 0;
	vm->sp = -1;
	vm->locals = (int*)malloc(sizeof(int)*datasize);
	if (!vm->locals) {
		VM_delete(vm);
		return NULL;
	}
	vm->stack = (int*)malloc(sizeof(int)*MAX_STACK);
	if (!vm->stack) {
		VM_delete(vm);
		return NULL;
	}
	return vm;
}

/* VM_delete:  destroys VM object */
void VM_delete(VM *vm)
{
	if (vm) {
		if (vm->locals)
			free(vm->locals);
		if (vm->stack)
			free(vm->stack);
		free(vm);
	}
}

/* VM_run:  runs the virtual machine */
void VM_run(VM *vm)
{
	do {
		int opcode = NCODE(vm); /* fetch instruction */
		int v, addr, offset, a, b, argc, rval;
		
		switch(opcode) {
			case OP_HALT:
				return;
			break;
			
			case OP_CONST:
				v = NCODE(vm);	/* get next value from code */
				PUSH(vm, v);	/* move to top of stack */
			break;
			
			case OP_ADD:
				b = POP(vm);	/* get second value */
				a = POP(vm);	/* get first value */
				PUSH(vm, a + b);	/* push the answer to stack */
			break;
			
			case OP_SUB:
				b = POP(vm);	/* get second value */
				a = POP(vm);	/* get first value */
				PUSH(vm, a - b);	/* push the answer to stack */
			break;
			
			case OP_MUL:
				b = POP(vm);	/* get second value */
				a = POP(vm);	/* get first value */
				PUSH(vm, a * b);	/* push the answer to stack */
			break;
			
			case OP_LT:
				b = POP(vm);	/* get second value */
				a = POP(vm);	/* get first value */
				PUSH(vm, (a < b) ? 1 : 0);	/* push answer to stack */
			break;
			
			case OP_EQ:
				b = POP(vm);	/* get second value */
				a = POP(vm);	/* get first value */
				PUSH(vm, (a == b) ? 1 : 0);	/* push answer to stack */
			break;
			
			case OP_JMP:
				addr = NCODE(vm);
				vm->pc = addr;	/* unconditional jump to address */
			break;
			
			case OP_JMPT:
				addr = NCODE(vm);	/* get address for jump instruction */
				if (POP(vm)) {		/* if true, then jump */
					vm->pc = addr;	/* make a jump */
				}
			break;
			
			case OP_JMPF:
				addr = NCODE(vm);	/* get address for jump instruction */
				if (!POP(vm)) {		/* if false, then jump */
					vm->pc = addr;	/* make a jump */
				}
			break;
			
			case OP_LOAD:
				offset = NCODE(vm);	/* get next value from code */
				PUSH(vm, vm->stack[vm->fp+offset]);	/* put on stack */
			break;
			
			case OP_GLOAD:
				addr = POP(vm);		/* get pointer address */
				v = vm->locals[addr];	/* load value from memory */
				PUSH(vm, v);		/* put on top of stack */
			break;
			
			case OP_STORE:
				v = POP(vm);		/* get value from stack */
				offset = NCODE(vm);	/* get relative pointer address */
				vm->locals[vm->fp+offset] = v;	/* store it */
			break;
			
			case OP_GSTORE:
				v = POP(vm);		/* get value from stack */
				addr = NCODE(vm);	/* get pointer address from code */
				vm->locals[addr] = v;	/* store to memory */
			break;
			
			case OP_CALL:
				addr = NCODE(vm);	/* get next address as procedure */
				argc = NCODE(vm);	/* number of args to load */
				PUSH(vm, argc);		/* save num args */
				PUSH(vm, vm->fp);	/* save function pointer */
				PUSH(vm, vm->pc);	/* save instruction pointer */
				vm->fp = vm->sp;	/* set new frame pointer */
				vm->pc = addr;		/* move ins pointer to procedure */
			break;
			
			case OP_RET:
				rval = POP(vm);		/* pop return value off stack */
				vm->sp = vm->fp;	/* return from procedure address */
				vm->pc = POP(vm);	/* restore instruction pointer */
				vm->fp = POP(vm);	/* restore frame pointer */
				argc = POP(vm);		/* how many args procedure has */
				vm->sp -= argc;		/* discard all of args left */
				PUSH(vm, rval);		/* leave return value on stack */
			break;
			
			case OP_POP:
				--vm->sp;	/* throw away value on top of stack */
			break;
			
			case OP_PRINT:
				v = POP(vm);		/* pop off top */
				printf("%d\n", v);	/* print it */
			break;
			
			default:
			break;
		}
	} while(1);
}
