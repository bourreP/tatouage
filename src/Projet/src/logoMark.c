#include <stdio.h> 
#include "matrix.h"
#include <highgui.h>//<opencv/highgui.h>
#include <cv.h>//<opencv/cv.h>
#include "global.h"


void logoToBin (IplImage *Logo){

  int i,j;
  CvScalar s;  
  double **mat;
  mat=alocamd(Logo->width,Logo->height);
  
  if ((Mark=fopen("Resultat/Marque.txt","w"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }

  for (i=0;i<Logo->width;i++){
    for (j=0;j<Logo->height;j++){

      s=cvGet2D(Logo,j,i);
      mat[i][j]=s.val[0];
      //printf("%3d ",(int)mat[i][j]);

      if((int)mat[i][j]>100)
	fprintf(Mark,"%d\n",1);
      else
	fprintf(Mark,"%d\n",0);
    }
    //printf("\n");
  }
  fclose(Mark);
  dalocd(mat,Logo->width);
}

void markToLogo (IplImage *Logo){

  int i,j;
  IplImage *LogRec;
  int m;
  double **mat;
  CvScalar s;

  mat=alocamd(Logo->width,Logo->height);
  LogRec=cvCreateImage(cvGetSize(Logo),Logo->depth,Logo->nChannels) ; 

  if ((MarkDet=fopen("Resultat/MarqueDetectee.txt","r"))==NULL){
    printf("Erreur ouverture fichier 1.\n");
    exit (EXIT_FAILURE);
  }

  for (i=0;i<Logo->width;i++)
    for(j=0;j<Logo->height;j++){

      fscanf(MarkDet,"%d\n",&m);
      mat[i][j]=m;
      s.val[0]=mat[i][j]*255;
      //      printf("Mais Allooooo quoi !\n");
      cvSet2D(LogRec,j,i,s);
      //      printf("Allooooo quoi !\n");
    }
  
  fclose(MarkDet);
  cvNamedWindow("Logo initial",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Logo initial",Logo); // affiche de imgHSV
  cvNamedWindow("Logo récupéré",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Logo récupéré",LogRec); // affiche de imgHSV
  dalocd(mat,Logo->width);
  cvReleaseImage(&LogRec);
}

