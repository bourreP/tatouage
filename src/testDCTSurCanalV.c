#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>

#include "dct.h"
#include "matrix.h"

int main (int argc, char ** argv)
{
	const char *fileName = "./lena.jpg";

	double** V;
	double** VDCT;
	int i;
	int j;
	CvScalar s;
	CvScalar s_img;

	if (argc > 1)
	{
		fileName = argv[1];
	}

	IplImage* src = cvLoadImage ( fileName, 3);
	IplImage* dct = cvCreateImage ( cvGetSize(src) , src->depth, src->nChannels);
	IplImage* img = cvCreateImage( cvGetSize(src), src->depth, 1);

	/**
	*Y  =      (0.257 * R) + (0.504 * G) + (0.098 * B) + 16
	*Cr = V =  (0.439 * R) - (0.368 * G) - (0.071 * B) + 128
	*Cb = U = -(0.148 * R) - (0.291 * G) + (0.439 * B) + 128
	**/	
	
	cvCvtColor (src, dct, CV_BGR2HSV);

	/**
	*On va travailler sur le canal V
	**/
	

	//Allocation de la matrice correspondant au canal V

	V = (double**) malloc(dct->width* sizeof(double*));

	for (i = 0; i < dct->width; i++)
	{
		V[i] = (double*) malloc(dct->height*sizeof(double));
	}

	//Initialisation de la matrice V à 0

	for (i = 0; i <src->width; i++)
	{
		for (j = 0; j < src->height; j++)
		{
			V[i][j] = 0;
		}
	}

	//On récupère les valeurs du canal V dans la matrice associée à celui-ci

	for (i = 0; i < src->width; i++)
	{
		for (j = 0; j < src->height; j++)
		{
			s = cvGet2D(dct,i,j);
			V[i][j] = s.val[2];
		}
	}
	

	//Allocation de la matrice VDCT (deuxième méthode)

	VDCT = alocamd( src->width, src->height);

	//Initialisation à 0 de VDCT

	for (i = 0; i <src->width; i++)
	{
		for (j = 0; j < src->height; j++)
		{
			VDCT[i][j] = 0;
		}
	}

	//Transformation DCT de la matrice V associé au canal "V" vers la matrice VDCT

	dct2dim( V, VDCT, src->width, src->height);

	//On met le VDCT comprenant le canal V (et seulement celui-ci) après transformation DCT dans le canal 0 de img

	for (i = 0; i < src->width; i++)
	{
		for (j = 0; j < src->height; j++)
		{
			s_img = cvGet2D(img,i,j);
			s_img.val[0] = VDCT[i][j];
			cvSet2D(img, i, j, s_img);
		}
	}

	//Affichage

	cvNamedWindow("YUV", CV_WINDOW_AUTOSIZE);
	cvShowImage("YUV", img);
	cvWaitKey(0);
	cvDestroyAllWindows();
}
