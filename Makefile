
CC=gcc
CFLAGS=-g -Wall -std=c99 -ftrapv -O2 -Werror -Wshadow -Wundef -save-temps -Werror-implicit-function-declaration
RM=rm -f

TARGET=bin/animals
SDIR = src

_SRC=main.c myfn.c

SRC=$(patsubst %, $(SDIR)/%, $(_SRC))

OBJS = $(patsubst %.c, %.o, $(SRC))

all: clean build

$(TARGET): build

build: .compilemsg $(OBJS)
	@-printf '\e[36mLinking\e[0m\n'
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)
	
.compilemsg:
	@-printf '\e[36mCompilation\e[0m\n'

run:
	@-printf '\e[36mLaunching $(TARGET)\e[0m\n'
	@-./$(TARGET)


depend: .depend


.depend: $(SRC)
	$(RM) ./.depend
	$(CC) $(CFLAGS) -MM $^>>./.depend;


clean:
	@-printf '\e[36mClean up\e[0m\n'
	$(RM) *~ src/*~ *.i src/*.i *.s src/*.s *.o src/*.o $(TARGET)
	
include .depend
