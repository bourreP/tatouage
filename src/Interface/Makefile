#
## Variables:
#
CC = gcc -g
EXEC = test
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)


#
## Flags d'erreurs:
#
ERROR_CFLAGS = -Wall -W -pedantic


#
## Flags pour le compilateur:
#
GMOD_CFLAGS = $$(pkg-config --cflags gmodule-2.0)
GTK_CFLAGS = $$(pkg-config --cflags gtk+-3.0)

CFLAGS = $(ERROR_FLAGS) $(GMOD_CFLAGS) $(GTK_CFLAGS)


#
## Flags pour l'editeur de liens:
#
GMOD_LDFLAGS = $$(pkg-config --libs gmodule-2.0)
GTK_LDFLAGS = $$(pkg-config --libs gtk+-3.0)

LDFLAGS = $(ERROR_FLAGS) $(GMOD_LDFLAGS) $(GTK_LDFLAGS)


#
## Construction du programme:
#
all: $(EXEC) clean

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

#
## Nettoyage:
#
clean:
	rm -f *.o *~ core $(BIN)
