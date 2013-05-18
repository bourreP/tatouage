all: test clean
CC = gcc -O2

test: main.o callback.o configuration.o fenetrePrincipale.o
	$(CC) -o test callback.o configuration.o fenetrePrincipale.o main.o  $$(pkg-config --libs gmodule-2.0) $$(pkg-config --libs gtk+-3.0)

main.o: main.c
	$(CC) -c main.c  $$(pkg-config --cflags gmodule-2.0) $$(pkg-config --cflags gtk+-3.0) 

fenetrePrincipale.o: fenetrePrincipale.c fenetrePrincipale.h
	$(CC) -c fenetrePrincipale.c  $$(pkg-config --cflags gmodule-2.0) $$(pkg-config --cflags gtk+-3.0) 

configuration.o: configuration.c configuration.h
	$(CC) -c configuration.c  $$(pkg-config --cflags gmodule-2.0) $$(pkg-config --cflags gtk+-3.0) 

callback.o: callback.c callback.h
	$(CC) -c callback.c  $$(pkg-config --cflags gmodule-2.0) $$(pkg-config --cflags gtk+-3.0) 

clean:
	rm *.o
