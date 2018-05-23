CC?=cc
CFLAGS?=-std=c89
LDFLAGS?=

SOURCES:=$(wildcard *.c)
OBJECTS:=$(SOURCES:.c=.o)
TARGET=csyntax

.PHONY: all clean
all: $(TARGET)

%.o: %.c
	@echo CC $(CFLAGS) -o $@ -c $<
	@$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS)
	@echo CCLD $(CFLAGS) $(LDFLAGS) -o $@ $^
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	@echo rm -f *~ $(OBJECTS) $(TARGET)
	@rm -f *~ $(OBJECTS) $(TARGET)
