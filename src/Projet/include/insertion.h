#include <stdio.h> 
#include "matrix.h"
#include <math.h>
#include <highgui.h>//<opencv/highgui.h>
#include <cv.h>//<opencv/cv.h>
#include "dct.h"
#include "fonctions.h"

void selection(double **Mv,int N,IplImage *img);
void generationPar(int N,IplImage *img,IplImage *Logo);
void insertionMarque ( double **blocT, int N, double key_i,int mes_i);
void Insertion (IplImage *img,int N,int *p);


