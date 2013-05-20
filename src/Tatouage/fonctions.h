#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h> 
#include <math.h>
#include <highgui.h>
#include <cv.h>

#include "dct.h"
#include "matrix.h"
#include "global.h"

void echanger ( int *px, int *py );
void echangerDouble (double *px, double *py);
void triAbulles ( double *t,int *x,int *y,int N );
void calculPSNR (IplImage *img);
void chargerImage (char *image);
void chargerLogo (int arg, char *logo);
void matToImg (double **Mat, IplImage *imgSRC,IplImage *imgDST );
void extractionBloc (double **Mat, int i, int j, int N, double **bloc);
void extractionCanalV (double **Mat, IplImage *imgHSV);
void insertionBloc ( double **bloc, int posx, int posy, int N, double **Mat);
void DCT (double **Mat, double **MTr, IplImage *imgHSV,int N);

#endif
