
CC=gcc
CFLAGS=-g -Wall -std=gnu99 -O0 -Wfatal-errors
#-Werror-implicit-function-declaration -Werror  -Wundef -ftrapv -O2 -Wshadow -save-temps
RM=rm -f

TARGET=animals
SDIR = src

_SRC=main.c ui.c utils.c colors.c log.c

SRC=$(patsubst %,$(SDIR)/%,$(_SRC))

OBJS = $(patsubst %.c,%.o,$(SRC))

all: purge build clean

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
	@$(RM) ./.depend
	$(CC) $(CFLAGS) -MM $^>>./.depend;


purge:
	@-printf '\e[36mPurge\e[0m\n'
	$(RM) *~ src/*~ *.i *.s *.o src/*.o $(TARGET)


clean:
	@-printf '\e[36mClean\e[0m\n'
	$(RM) *~ src/*~ *.o src/*.o *.i *.s 
	
include .depend
