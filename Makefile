#
# Makefile for C-Minus
# Gnu C Version
# K. Louden 2/3/98
#
# Modified by Seongjun Kim, 2015

CC = gcc

CFLAGS = -Wall -g

OBJS = y.tab.o lex.yy.o main.o util.o symtab.o analyze.o midcode.o

compiler: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o compiler

main.o: main.c globals.h util.h analyze.h 
	$(CC) $(CFLAGS) -c main.c

util.o: util.c util.h globals.h
	$(CC) $(CFLAGS) -c util.c

symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

analyze.o: analyze.c globals.h symtab.h analyze.h
	$(CC) $(CFLAGS) -c analyze.c

midcode.o:globals.h symtab.h midcode.h midcode.c
	$(CC) $(CFLAGS) -c midcode.c

lex.yy.o: compiler.l util.h globals.h
	flex -o lex.yy.c compiler.l
	$(CC) $(CFLAGS) -c lex.yy.c

y.tab.o: compiler.y globals.h
	bison -d compiler.y --yacc
	$(CC) $(CFLAGS) -c y.tab.c

clean:
	-rm compiler
	-rm y.tab.c
	-rm y.tab.h
	-rm lex.yy.c
	-rm $(OBJS)

test: compiler
	-./compiler test.cm

all: compiler
