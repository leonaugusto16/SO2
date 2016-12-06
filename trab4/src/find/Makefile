CC = gcc
CFLAGS = -I.
DEPS = find.h 
OBJ = find.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
find: $(OBJ)
	$(CC) -o $@ $< $(CFLAGS)

