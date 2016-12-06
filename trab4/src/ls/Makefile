CC = gcc
CFLAGS = -I.
DEPS = ls.h
OBJ = ls.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
ls: $(OBJ)
	$(CC) -o $@ $< $(CFLAGS)
