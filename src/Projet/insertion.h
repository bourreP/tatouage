#ifndef INSERTION_H
#define INSERTION_H

#include <stdio.h> 
#include <math.h>
#include <highgui.h>
#include <cv.h>

#include "dct.h"
#include "fonctions.h"
#include "matrix.h"

void selection(double **Mv,int N,IplImage *img);
void generationPar(int N,IplImage *img,IplImage *Logo);
void insertionMarque ( double **blocT, int N, double key_i,int mes_i);
void Insertion (IplImage *img,int N,int *p);

#endif
