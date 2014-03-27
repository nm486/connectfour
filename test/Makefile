# SAMPLE, modify or delete at will
PROGNAME = test_C4

CC=gcc
GIVEN_OBJECTS=
OBJECTS = board.o connectfour.o unittests.o
DEPS = options.h board.h connectfour.h
# -g for debugging, see about o3 and other compilers later
CFLAGS= -g -lm -lcunit
RM = rm -f

$(PROGNAME) : $(OBJECTS) $(GIVEN_OBJECTS)
	$(CC) $(CFLAGS) $(GIVEN_OBJECTS) $(OBJECTS) -o $@ $(LINK)

%.o: $(BASE_DIR)/../%.c $(BASE_DIR)/../$(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJECTS) $(PROGNAME)

