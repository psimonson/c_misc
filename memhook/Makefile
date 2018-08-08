CC=cc
CFLAGS=-std=c89
LDFLAGS=

all: prog1 libmemhook

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

prog1: prog1.o
	$(CC) $(LDFLAGS) -o $@ $^

memhook.o: memhook.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

libmemhook: memhook.o
	$(CC) $(LDFLAGS) -shared -ldl -o $@.so $^

clean:
	rm -f *.o *.so prog1
