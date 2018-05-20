CFLAGS?=-std=c89
LDFLAGS?=

.PHONY: all clean
all: $(patsubst %.c,%.out,$(wildcard *.c))

%.out: %.c Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $(@:.out=)

clean: $(patsubst %.c, %.clean, $(wildcard *.c))

%.clean:
	rm -f $(@:.clean=)
