CC=cc
CFLAGS=-std=gnu89 -g
LDFLAGS=

all: prog1 prog2 prog3 memhook

prog1: prog1.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

prog2: prog2.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

prog3: prog3.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

memhook: memhook.c
	$(CC) $(CFLAGS) $(LDFLAGS) -fPIC -shared -o $@.so $^ -ldl

clean:
	rm -f *.so prog1 prog2 prog3
