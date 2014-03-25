SRC=board.c connectfour.c main.c 
OBJ=$(SRC:.c=.o)
CC=pgcc
CFLAGS= -O3


all: C4

C4: $(OBJ)
	$(CC) $(CFLAGS)  -o $@  $(OBJ) -lm

clean:
	rm -f MD $(OBJ) 

$(OBJ) : options.h board.h connectfour.h Makefile


