CFLAGS=-std=gnu89 -Wall -g -c
LDFLAGS=-std=gnu89 -Wall -g
LIBS=-lgit2

.PHONY: all clean
all: gitgrab getch_test

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

gitgrab: gitgrab.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

getch_test: getch_test.o getch.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o gitgrab getch_test
