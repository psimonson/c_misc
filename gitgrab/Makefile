CFLAGS=-std=gnu89 -Wall -g -c
LDFLAGS=-std=gnu89 -Wall -g
LIBS=-lgit2

.PHONY: all clean
all: gitgrab

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

gitgrab: gitgrab.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f *.o gitgrab
