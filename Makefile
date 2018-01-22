# $Header: /home/johnl/flnb/code/sql/RCS/Makefile,v 2.1 2009/11/08 02:53:39 johnl Exp $
# Companion source code for "flex & bison", published by O'Reilly
# Media, ISBN 978-0-596-15597-1
# Copyright (c) 2009, Taughannock Networks. All rights reserved.
# See the README file for license conditions and contact info.

CC = g++ -g -w
LEX = flex
YACC = bison
CFLAGS = -DYYDEBUG=1

PROGRAMS = parsql
PROGRAMSA = parsqla
PROGRAMSSO = parsqlso
CLEAR = clear

all:	${PROGRAMS} ${PROGRAMSA} ${PROGRAMSSO} ${CLEAR}

# chapter 4

parsql:	parsql.tab.o parsql.o main.o
	${CC} -o $@ parsql.tab.o parsql.o main.o

parsqla:	parsql.tab.o parsql.o
	ar -r libparsql.a parsql.tab.o parsql.o

parsqlso: parsql.tab.c parsql.c
	g++ -w -g -c -fpic parsql.tab.c -o parsql.tab.so.o
	g++ -w -g -c -fpic parsql.c -o parsql.so.o
	g++ -shared -o libparsql.so parsql.tab.so.o parsql.so.o

parsql.tab.c parsql.tab.h:	parsql.y
	${YACC} -vd parsql.y

parsql.c:	parsql.l
	${LEX} -o $@ $<

parsql.o:	parsql.c parsql.tab.h

clear:
	rm -rf *.o

clean:
	rm -f parsql parsql.tab.c parsql.tab.h parsql.c *.o *.a parsql.output libparsql.* *.sql .input.sql

.SUFFIXES:	.l .y .c

