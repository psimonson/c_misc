CFLAGS=-std=gnu89 -Wall -c
LDFLAGS=-std=gnu89 -Wall

SOURCES=main.c vm.c
OBJECTS=$(SOURCES:.c=.o)
TARGETS=svm

.PHONY: all clean
all: $(TARGETS)

%.o: %.c
	@echo CC $(CFLAGS) -o $@ $<
	@$(CC) $(CFLAGS) -o $@ $<

$(TARGETS): $(OBJECTS)
	@echo CCLD $(LDFLAGS) -o $@ $^
	@$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f *~ $(OBJECTS) $(TARGETS)
