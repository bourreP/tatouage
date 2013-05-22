all: Lancement Tatouage clean

CC = gcc -g

CFLAGSGTK = $$(pkg-config --cflags gmodule-2.0) $$(pkg-config --cflags gtk+-3.0) 
LFLAGSGTK = $$(pkg-config --libs gmodule-2.0) $$(pkg-config --libs gtk+-3.0)
CFLAGSCV = $$(pkg-config --cflags opencv) 
LFLAGSCV = $$(pkg-config --libs opencv)

Lancement: main.o callback.o configuration.o fenetrePrincipale.o
	$(CC) -o Lancement callback.o configuration.o fenetrePrincipale.o main.o $(LFLAGSGTK)

Tatouage: Tatouage.o dct.o matrix.o logoMark.o insertion.o detection.o fonctions.o
	$(CC) -o Tatouage Tatouage.o dct.o matrix.o logoMark.o insertion.o detection.o fonctions.o $(LFLAGSCV) -lm

main.o: main.c
	$(CC) -c main.c $(CFLAGSGTK)

fenetrePrincipale.o: fenetrePrincipale.c fenetrePrincipale.h
	$(CC) -c fenetrePrincipale.c $(CFLAGSGTK) 

configuration.o: configuration.c configuration.h
	$(CC) -c configuration.c $(CFLAGSGTK) 

callback.o: callback.c callback.h
	$(CC) -c callback.c $(CFLAGSGTK) 

Tatouage.o: Tatouage.c
	$(CC) -c Tatouage.c $(CFLAGSCV)

dct.o: dct.c dct.h
	$(CC) -c dct.c

matrix.o: matrix.c matrix.h
	$(CC) -c matrix.c

logoMark.o: logoMark.c logoMark.h
	$(CC) -c logoMark.c $(CFLAGSCV)

insertion.o: insertion.c insertion.h
	$(CC) -c insertion.c $(CFLAGSCV) -lm

detection.o: detection.c detection.h
	$(CC) -c detection.c $(CFLAGSCV)

fonctions.o: fonctions.c fonctions.h
	$(CC) -c fonctions.c $(CFLAGSCV)

clean:
	rm *.o
