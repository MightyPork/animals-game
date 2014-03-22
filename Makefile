
CC=gcc
CFLAGS=-g -Wall -std=c99 -ftrapv -O2 -Werror -Wshadow -Wundef -save-temps -Werror-implicit-function-declaration
RM=rm -f

TARGET=bin/animals
SDIR = src

_SRC=main.c myfn.c

SRC=$(patsubst %, $(SDIR)/%, $(_SRC))

OBJS = $(patsubst %.c, %.o, $(SRC))

all: clean pf build

pf:
	@-printf '\e[36mCompiling...\e[0m\n'
	

$(TARGET): build

build: $(OBJS)
	@-printf '\n\e[36mLinking...\e[0m\n'
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)
	@-printf '\n'

run:
	@-./$(TARGET)


depend: .depend


.depend: $(SRC)
	$(RM) ./.depend
	$(CC) $(CFLAGS) -MM $^>>./.depend;


clean:
	@-printf '\e\n[36mCleaning...\e[0m\n'
	$(RM) *~ src/*~ *.i src/*.i *.s src/*.s *.o src/*.o $(TARGET)
	@-printf '\n'
	
include .depend
