SRC=connectfour.c main.c 
OBJ=$(SRC:.c=.o)
CC=pgcc
CFLAGS= -g


all: C4

C4: $(OBJ)
	$(CC) $(CFLAGS)  -o $@  $(OBJ) -lm

clean:
	rm -f MD $(OBJ) 

$(OBJ) : connectfour.h Makefile


