CC=cc
CFLAGS?=-std=c89
LDFLAGS=

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=ast

all: $(TARGET)

%.o: %.c
	@echo CC $(CFLAGS) -c -o $@ $<
	@$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	@echo CCLD $(CFLAGS) $(LDFLAGS) -o $@ $^
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	@echo RM -f *~ $(OBJECTS) $(TARGET)
	@rm -f *~ $(OBJECTS) $(TARGET)
 
