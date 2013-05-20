all: Tatouage clean

CC = gcc -g
CFLAGS = $$(pkg-config --cflags opencv) 
LFLAGS = $$(pkg-config --libs opencv)

Tatouage: Tatouage.o dct.o matrix.o logoMark.o insertion.o detection.o fonctions.o
	$(CC) -o Tatouage Tatouage.o dct.o matrix.o logoMark.o insertion.o detection.o fonctions.o $(LFLAGS)

dct.o: dct.c dct.h
	$(CC) -c dct.c

matrix.o: matrix.c matrix.h
	$(CC) -c matrix.c

logoMark.o: logoMark.c logoMark.h
	$(CC) -c logoMark.c $(CFLAGS)

insertion.o: insertion.c insertion.h
	$(CC) -c insertion.c $(CFLAGS)

detection.o: detection.c detection.h
	$(CC) -c detection.c $(CFLAGS)

fonctions.o: fonctions.c fonctions.h
	$(CC) -c fonctions.c $(CFLAGS)

clean:
	rm *.o
