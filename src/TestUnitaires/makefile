all: test clean

CC = gcc -g

CFLAGSGTK = $$(pkg-config --cflags gmodule-2.0) $$(pkg-config --cflags gtk+-3.0) 
LFLAGSGTK = $$(pkg-config --libs gmodule-2.0) $$(pkg-config --libs gtk+-3.0)
CFLAGSCV = $$(pkg-config --cflags opencv) 
LFLAGSCV = $$(pkg-config --libs opencv)

test: test.o dct.o matrix.o logoMark.o insertion.o detection.o fonctions.o
	$(CC) -o test test.o dct.o matrix.o logoMark.o insertion.o detection.o fonctions.o $(LFLAGSCV) -lm

test.o: test.c
	$(CC) -c test.c $(CFLAGSCV)

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
