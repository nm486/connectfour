# SAMPLE, modify or delete at will
PROGNAME = test_C4

CC=pgcc
GIVEN_OBJECTS=
OBJECTS = board.o connectfour.o main.o unittests.o
DEPS = options.h board.h connectfour.h
# -g for debugging, see about o3 and other compilers later
CFLAGS= -Wall -std=c99 -pedantic -g -lm -lcunit
RM = rm -f

$(PROGNAME) : $(OBJECTS) $(GIVEN_OBJECTS)
	$(CC) $(CFLAGS) $(GIVEN_OBJECTS) $(OBJECTS) -o $@ $(LINK)

%.o: $(BASE_DIR)/../%.c $(BASE_DIR)/../$(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJECTS) $(PROGNAME)

