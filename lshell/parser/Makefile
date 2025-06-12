
# src/parser/Makefile

CC := gcc

CFLAGS := -Wall -Wextra -std=c99 -g -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -I.. -Isrc -Isrc/shell -Isrc/parser
EX := flex
YACC := bison

LEX_SRC := lexer.l
YACC_SRC := parser.y

LEX_C := lexer.c
LEX_H := lexer.h
YACC_C := parser.c
YACC_H := parser.h

OBJS := parser.o lexer.o

.PHONY: all clean move

all: $(OBJS)
	@mkdir -p build
	@mv -f $(OBJS) build/
	@mv -f $(LEX_C) $(LEX_H) build/
	@mv -f $(YACC_C) $(YACC_H) build/

parser.o: $(YACC_C)
	$(CC) $(CFLAGS) -c $(YACC_C) -o parser.o

lexer.o: $(LEX_C)
	$(CC) $(CFLAGS) -c $(LEX_C) -o lexer.o

$(YACC_C) $(YACC_H): $(YACC_SRC)
	$(YACC) -d -o $(YACC_C) $(YACC_SRC)

$(LEX_C) $(LEX_H): $(LEX_SRC)
	$(LEX) --header-file=$(LEX_H) -o $(LEX_C) $(LEX_SRC)

clean:
	rm -f *.o *.c *.h
	rm -rf build

