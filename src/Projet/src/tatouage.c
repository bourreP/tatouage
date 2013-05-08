#include <stdio.h> 
#include "matrix.h"
#include <math.h>
#include <highgui.h>//<opencv/highgui.h>
#include <cv.h>//<opencv/cv.h>
#include "dct.h"
#include "global.h"
#include "fonctions.h"
#include "insertion.h"
#include "detection.h"
#include "logoMark.h"

int main (int argc, char **argv){

  int i;

  double **Mv;               // Matrice initiale du canal V de l'image HSV 
  //double **MTr;

  IplImage *img;            // Image initiale en  RGB
  IplImage *imgHSV;         // Image initiale en HSV
  IplImage *imgHSVTat;         // Image tatouée en HSV
  IplImage *imgTat;           // Image tatouée en RGB
  IplImage *Logo; 
  
  if (argv[1]==NULL)
    img=cvLoadImage("source.jpg",1);
  else
    img=cvLoadImage(argv[1],1);

  if (argv[2]!=NULL)
    Logo=cvLoadImage (argv[2],0);
  else
    Logo=cvLoadImage ("logo.png",0); 
  
  imgHSV=cvCreateImage(cvGetSize(img),img->depth,img->nChannels) ; 
  imgHSVTat=cvCreateImage(cvGetSize(img),img->depth,img->nChannels) ;
  imgTat=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);

  int N=4; //définition de la taille des blocs pour la DCT
  a=0.68;
  pas=300;
  NWB=(Logo->width)*(Logo->height);
  
  int p[3];  
  p[0]=CV_IMWRITE_JPEG_QUALITY;
  p[1]=100;
  p[2]=0;
 
  cvNamedWindow("Image source",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image source",img); // affiche de imgHSV
      

  /** Génération aléatoire des paramètres du tatouage **/
  
  srand(time(NULL));
  generationPar(N,img);
  logoToBin (Logo);
 
  /** Enregistrement des paramètres du tatouage dans des fichiers textes **/
  
  enregistrementPar();
  
  /**     Conversion de l'image RGB en HSV        **/
  
  cvCvtColor(img,imgHSV,CV_BGR2HSV); // On met dans imgHSV l'image sources en HSV
  cvNamedWindow("Image source HSV",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image source HSV",imgHSV); // affiche de imgHSV
      
  /**    On extrait le canal V     **/
  
  Mv=alocamd(img->width, img->height); 
  //  MTr=alocamd(img->width, img->height);// Allocation de Mv
  extractionCanalV(Mv,imgHSV);
  bloc=alocamd(N,N);                     // Allocation des blocs
  blocT=alocamd(N,N);                    // Allocation des blocs transformés
  //printf("Test\n");
  //  DCT (Mv,MTr,img,N);
  //printf("Test\n");
  //  selectionBloc(Mv,N,img);
  //printf("Test\n");

  if ((Mark=fopen("Marque.txt","r"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }
   
  if ((POS=fopen("position_bloc.txt","r"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }
  

  for (i=0;i<NWB;i++) {
    fscanf(Mark,"%d\n",&mes);
    //printf("Test\n");
    //    fscanf(POS,"%d %d\n",&posx,&posy);
    //printf("Test\n");
    extractionBloc ( Mv, posx[i], posy[i],N, bloc);      // Extraction des blocs
    dct2dim (bloc, blocT,N,N);              // DCT sur le bloc sélectionné
    insertion (blocT,N,key[i],mes);      // Insertion du message et validation de l'insertion
    dct2dim_inv (blocT, bloc,N,N);          // DCT inverse sur le bloc tatoué
    insertionBloc (bloc, posx[i],posy[i],N,Mv); // Insertion du bloc tatoué dans la matrice de l'image
  }

  //  fclose(POS);
  //fclose(Mark);

  matToImg(Mv,imgHSV,imgHSVTat); // Création de l'image tatouée à partir de Mv et de l'image source
  cvCvtColor(imgHSVTat,imgTat,CV_HSV2BGR); // On convertit l'image HSV tatouée en image RGB

  cvNamedWindow("Image HSV tatouée",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image HSV tatouée",imgHSVTat);
  cvNamedWindow("Image tatouée",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image tatouée",imgTat);
  cvSaveImage ("imageTatouee.jpg", imgTat, p);

  detectionMarque(N);  //Détection des blocs marqués

  markToLogo(Logo);  //Récupération de la marque
  
  cvWaitKey(0);
  cvDestroyAllWindows();

  cvReleaseImage(&img);
  cvReleaseImage(&imgTat);
  cvReleaseImage(&imgHSV);
  cvReleaseImage(&imgHSVTat);
  cvReleaseImage(&Logo);
  
  dalocd(bloc,N);
  dalocd(blocT,N);
  //  freevi(mes);
  freevi(posx);
  freevi(posy);
  freevd(key);  
  
  return EXIT_SUCCESS;

}
