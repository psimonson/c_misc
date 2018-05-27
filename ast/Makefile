CC=cc
CFLAGS?=-std=c89
LDFLAGS=

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=ast

all: $(TARGET)

%.yy.c: %.l
	@echo flex $<
	@flex $<

%.tab.c: %.y
	@echo bison -d $<
	@bison -d $<

%.o: %.c
	@echo CC $(CFLAGS) -c -o $@ $<
	@$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): grammer.tab.o lex.yy.o $(OBJECTS)
	@echo CCLD $(CFLAGS) $(LDFLAGS) -o $@ $^
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	@echo RM -f *~ grammer.tab.* lex.yy.* $(OBJECTS) $(TARGET)
	@rm -f *~ grammer.tab.* lex.yy.* $(OBJECTS) $(TARGET)
 
