#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "matrix.h"
#include "dct.h"

void extractionBloc (double **Mat, int i, int j, int N, double **bloc);
void extractionCanalV (double **Mat, IplImage *imgHSV, int N);
void insertionBloc ( double **bloc, int posx, int posy, int N, double **Mat,CvScalar s);
void insertion ( double **blocT, int N, int pas, float a,double key,int mes);
