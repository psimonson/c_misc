#ifndef _VM_H_
#define _VM_H_

#define MAX_STACK 100

/* VM operation enumeration */
enum {
	OP_ADD = 1,	/* addition */
	OP_SUB,		/* subtract */
	OP_MUL,		/* muliply */
	OP_LT,		/* less Than */
	OP_EQ,		/* equal To */
	OP_JMP,		/* branch */
	OP_JMPT,	/* branch if true */
	OP_JMPF,	/* branch if false */
	OP_CONST,	/* push constant int */
	OP_LOAD,	/* load from local */
	OP_GLOAD,	/* load from global */
	OP_STORE,	/* store to local */
	OP_GSTORE,	/* store to global */
	OP_PRINT,	/* print value on top of stack */
	OP_POP,		/* throw away top of stack */
	OP_HALT,	/* stop program */
	OP_CALL,	/* call procedure */
	OP_RET		/* return from procedure */
};

/* VM data structure */
typedef struct {
	int *locals;
	int *code;
	int *stack;
	int pc;
	int sp;
	int fp;
} VM;

/* VM creating and destroying */
VM* VM_create(int *code, int pc, int datasize);
void VM_delete(VM *vm);
void VM_run(VM *vm);

#define PUSH(vm, v) vm->stack[++vm->sp] = v
#define PEEK(vm) vm->stack[vm->sp-1]
#define POP(vm) vm->stack[vm->sp--]
#define NCODE(vm) vm->code[vm->pc++]

#endif
