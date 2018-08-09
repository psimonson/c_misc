CC=cc
CFLAGS=-std=gnu89
LDFLAGS=

all: prog1 prog2 memhook

prog1: prog1.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

prog2: prog2.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

memhook: memhook.c
	$(CC) $(CFLAGS) $(LDFLAGS) -fPIC -shared -o $@.so $^ -ldl

clean:
	rm -f *.so prog1 prog2
