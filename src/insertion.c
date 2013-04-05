#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include "matrix.h"
#include "dct.h"
#include "fonctions.h"
#include <stdint.h>

int main (int argc, char **argv){

  int N=4; //définition de la taille des blocs pour la DCT
  int i,j;
  float a=0.6;
  int pas=10;
  double **Mv;               // Matrice initiale du canal V de l'image HSV 
  IplImage *img;            // Image initiale en  RGB
  IplImage *imgHSV;         // Image initiale en HSV
  IplImage *imgHSVTat;         // Image tatouée en HSV
  IplImage *imgTat;           // Image tatouée en RGB
  img=cvLoadImage(argv[1],3);
  imgHSV=cvCreateImage(cvGetSize(img),img->depth,img->nChannels) ; 
  imgHSVTat=cvCreateImage(cvGetSize(img),img->depth,img->nChannels) ;
  imgTat=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
  srand(time(NULL));
  int posx = N*(rand()%((img->width)/N));
  int posy = N*(rand()%((img->height)/N));
  double key=rand()/((double)INT_MAX);
  int mes=rand()%2;
  FILE *KEY,*POS;

  printf("Position en x du bloc : %d\n", posx);
  printf("Position en y du bloc : %d\n", posy); 
  printf("Clef : %lf\n",key);
  printf("Message : %d\n",mes);

  if ((POS=fopen("position_bloc.txt","w"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }
  fprintf(POS,"Position en x du bloc tatoué : %d\nPosition en y du bloc tatoué : %d\n",posx,posy);
  fclose (POS);

  if ((KEY=fopen("key.txt","w"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }
  fprintf(KEY,"Valeur de la clef : %f\n",key);
  fclose (KEY);

  cvNamedWindow("Image source",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image source",img);

  /**     Conversion de l'image RGB en HSV        **/
 
  cvCvtColor(img,imgHSV,CV_BGR2HSV); // On met dans imgHSV l'image sources en HSV
  cvNamedWindow("Image source HSV",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image source HSV",imgHSV); // affiche de imgHSV
      
  /**    On extrait le canal V     **/
 
  Mv=alocamd(img->width, img->height); // Allocation de Mv
  extractionCanalV(Mv,imgHSV, N);

  CvScalar s;
  double **bloc;
  double **blocT;
  bloc=alocamd(N,N);                     // Allocation des blocs
  blocT=alocamd(N,N);                    // Allocation des blocs transformés

  extractionBloc ( Mv, posx, posy,N, bloc);      // Extraction des blocs
  dct2dim (bloc, blocT,N,N);              // DCT sur le bloc sélectionné
  insertion (blocT,N,pas,a,key,mes);      // Insertion du message et validation de l'insertion
  dct2dim_inv (blocT, bloc,N,N);          // DCT inverse sur le bloc tatoué
  insertionBloc (bloc, posx,posy,N,Mv,s); // Insertion du bloc tatoué dans la matrice de l'image

  for(i=0; i<imgHSV->width; i++){         // Transformation de la matrice image en image HSV
    for(j=0; j<imgHSV->height; j++){

      s=cvGet2D(imgHSV,j,i);
      s.val[2]=Mv[i][j];
      cvSet2D(imgHSVTat,j,i,s);
    }
  }

  cvNamedWindow("Image HSV tatouée",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image HSV tatouée",imgHSVTat);

  cvCvtColor(imgHSVTat,imgTat,CV_HSV2BGR); // On convertit l'image HSV tatouée en image RGB

  cvNamedWindow("Image tatouée",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image tatouée",imgTat);
  cvWaitKey(0);
  cvDestroyAllWindows();

  return EXIT_SUCCESS;

}
