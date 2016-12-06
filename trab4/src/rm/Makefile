CC = gcc
CFLAGS = -I.
DEPS = rm.h
OBJ = rm.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
rm: $(OBJ)
	$(CC) -o $@ $< $(CFLAGS)

