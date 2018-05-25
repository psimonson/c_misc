CC?=cc
CFLAGS?=-std=c89 -g
LDFLAGS?=

SOURCES:=$(wildcard *.c)
OBJECTS:=$(SOURCES:.c=.o)
TARGET=csyn

.PHONY: all clean
all: $(TARGET)

%.o: %.c
	@echo CC $(CFLAGS) -o $@ -c $<
	@$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS)
	@echo CCLD $(CFLAGS) $(LDFLAGS) -o $@ $^
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

debug: clean $(TARGET)
	@echo gdb --batch --ex r --ex bt --ex q --args $(TARGET)
	@gdb --batch --ex r --ex bt --ex q --args $(TARGET)

clean:
	@echo rm -f *~ $(OBJECTS) $(TARGET)
	@rm -f *~ $(OBJECTS) $(TARGET)
