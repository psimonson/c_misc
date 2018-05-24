CC=cc
CFLAGS=-std=c89
LDFLAGS=

SOURCE=$(wildcard *.c)
OBJECTS=$(SOURCE:.c=.o)
TARGET=checker

.PHONY: all clean
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
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f ~* *.o lex.yy.* grammer.tab.* checker

