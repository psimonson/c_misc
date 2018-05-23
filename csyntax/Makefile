CC=cc
CFLAGS=-std=c89
LDFLAGS=

.PHONY: all clean
all: checker

lex.yy.c: lex.l
	@echo flex $^
	@flex $^

grammer.tab.c: grammer.y
	@echo bison -d grammer.y
	@bison -d grammer.y

checker: lex.yy.c grammer.tab.c main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f ~* lex.yy.* grammer.tab.* checker

