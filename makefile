CC=gcc
CFLAGS=-Wall
LDFLAGS=
EXEC=MST
SRC= fonctions.c main.c
OBJ =$(SRC:.c=.o)

all: $(EXEC)

MST: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: fonctions.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
