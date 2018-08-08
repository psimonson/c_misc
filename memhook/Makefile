CC=cc
CFLAGS=-std=c89
LDFLAGS=

all: prog1 libmemhook

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

prog1: prog1.o
	$(CC) $(CFLAGS) -o $@ $^

memhook.o: memhook.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

libmemhook: memhook.o
	$(CC) $(CFLAGS) -shared -ldl -o $@.so $^

clean:
	rm -f *.o *.so prog1
