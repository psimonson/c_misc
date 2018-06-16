CFLAGS=-std=c89 -Wall -Werror -Wno-unused-function
LDFLAGS=-std=c89 -Wall -Werror -Wno-unused-function

PROGS:=dcl undcl

all: $(PROGS)

%.o: %.c
	@echo CC $(CFLAGS) -c -o $@ $<
	@$(CC) $(CFLAGS) -c -o $@ $<

dcl: dcl.o
	@echo CCLD $(LDFLAGS) -o $@ $^
	@$(CC) $(LDFLAGS) -o $@ $^

undcl: undcl.o
	@echo CCLD $(LDFLAGS) -o $@ $^
	@$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o $(PROGS)
