#include <stdio.h>
#include <stdlib.h>
#include <cv.h> //<opencv/cv.h>
#include <highgui.h> //<opencv/cv.h>
#include "matrix.h"
#include "dct.h"
void extractionBloc (double **Mat, int i, int j, int N, double **bloc);
void extractionCanalV (double **Mat, IplImage *imgHSV, int N);
void insertionBloc ( double **bloc, int posx, int posy, int N, double **Mat);
void insertion ( double **blocT, int N, int pas, float a,double key_i,int mes_i);
