CC?=cc
CFLAGS?=-std=c89
LDFLAGS?=

SOURCES:=$(wildcard *.c)
OBJECTS:=$(SOURCES:.c=.o)
OBJECTS2:=grammer.tab.o lex.yy.o
TARGET=cc

.PHONY: all clean
all: grammer

grammer:
	bison -d grammer.y
	flex lex.l
	${MAKE} $(TARGET)

%.o: %.c
	@echo CC $(CFLAGS) -o $@ -c $<
	@$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS) $(OBJECTS2)
	@echo CCLD $(CFLAGS) $(LDFLAGS) -o $@ $^
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	@echo rm -f *~ $(OBJECTS2) grammer.tab.c grammer.tab.h lex.yy.c $(OBJECTS) $(TARGET)
	@rm -f *~ $(OBJECTS2) grammer.tab.c grammer.tab.h lex.yy.c $(OBJECTS) $(TARGET)
