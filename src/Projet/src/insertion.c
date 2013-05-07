#include <stdio.h> 
#include "matrix.h"
#include <math.h>
#include <highgui.h>//<opencv/highgui.h>
#include <cv.h>//<opencv/cv.h>
#include "dct.h"
#include "global.h"
#include "fonctions.h"

/* On sélectionne au hasard 20% des blocs de NxN de l'image, on calcul leur énergie, on les tri par ordre décroissant d'énergie, on sélectionne les 1024 de plus haute énergie et on enregistre leur position dans position_bloc.txt */

void selection(double **Mv,int N,IplImage *img){

  int i,j,k;
  double *ener;
  double En;

  srand(time(NULL));  

  posx=alocavi(((img->height*img->width)/(N*N*5)));
  posy=alocavi(((img->height*img->width)/(N*N*5)));
  ener=malloc(((img->height*img->width)/(N*N*5))*sizeof(double));

  if ((POS=fopen("position_bloc.txt","w"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }

  for(i=0;i<((img->height*img->width)/(N*N*5));i++){
    posx[i] = N*(rand()%((img->width)/N));
    posy[i] = N*(rand()%((img->height)/N));  
    extractionBloc ( Mv, posx[i], posy[i],N, bloc);      // Extraction des blocs
    dct2dim (bloc, blocT,N,N);  // L'énergie se calcule à partie de la DCT des blocs
    En=0;
    for(j=0;j<N;j++)
      for(k=0;k<N;k++)
	En+=blocT[j][k]*blocT[j][k];
    ener[i]=En;
  }

  triAbulles(ener,posx,posy,N); // On trie les blocs par énergie décroissantes

  for (i=0;i<NWB;i++)
    fprintf(POS,"%d %d\n",posx[i],posy[i]); // On enregistre les positions des blocs de plus haute énergie dans POS

  fclose(POS);
  free(ener);
}

void generationPar(int N,IplImage *img,IplImage *Logo){

  int i;
  srand(time(NULL));  

  key=alocavd(NWB); // On génère aléatoirement les clefs ( entre 0 et 0,25 )
  for(i=0;i<NWB;i++)
    key[i]=(((double)rand()/(RAND_MAX)/4));
  
  logoToBin (Logo); // On convertie le logo en binaires, ce sera le message à tatouer

  if ((KEY=fopen("key.txt","w"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }

  for (i=0;i<NWB;i++)
  fprintf(KEY,"%f\n",key[i]);
  fclose (KEY);

}

void insertionMarque (double **blocT,int N,double key_i,int mes_i){

  int i,j;
  int mes_dec;
  double aux1,aux2,w;           // Intermédiaires de calcul
  double Q;                     // Valeur test pour l'insertion
  double proj1,proj2;           // Projetés sur le masque
  proj1=0;
  proj2=0;

  float masque_t[4][4]= {
    {0,0.58,1.2,2.39},
    {0.58,1.12,1.49,2.3},
    {1.2,1.49,3.07,4.35},
    {2.39,2.3,4.35,7.25}
  };
  float Norme_masque=11.4492;
  
  double aux;
  double **blocT2;
  blocT2=alocamd(N,N);

  for (i=0;i<N;i++)                // Copie de blocT dans blocT2
    for (j=0;j<N;j++)
      blocT2[i][j]=blocT[i][j];
    
  
  for (i=0;i<N;i++)               // Transposée de blocT
    for(j=0;j<N;j++){

      aux=blocT[i][j];
      blocT[i][j]=blocT[j][i];
      blocT[j][i]=aux;
      }
  
  for (i=0;i<N;i++)
    for(j=0;j<N;j++)               // Projection sur le masque
      proj1+=(double)blocT[i][j]*masque_t[i][j]/Norme_masque;

  aux1= floor((proj1-pas*((float)mes_i/2+key_i))/pas+0.5);
  w = a*(aux1*pas-(proj1-pas*((float)mes_i/2+key_i)));  

  /*insertion*/

  for (i=0;i<N;i++)
    for(j=0;j<N;j++){
      //blocT[i][j]=0;
      blocT[i][j]=blocT2[i][j]+w*masque_t[i][j]/Norme_masque;
    }

  /*detection immédiate*/

  for (i=0;i<N;i++)
    for(j=0;j<N;j++)
      proj2+=(double)blocT[i][j]*masque_t[i][j]/Norme_masque;

  aux2=floor((proj2-pas*key_i)/(pas)+0.5);
  Q = aux2*pas-(proj2-pas*key_i);

  if (fabs(Q)<(1-a)*pas/2)
    mes_dec=0;
  else
    mes_dec=1;
 
  if(mes_dec!=mes_i){
    printf("Erreur lors de l'insertion.\n");
    exit(EXIT_FAILURE);
  }
  dalocd(blocT2,N);
}

void Insertion (IplImage *img,int N,int *p){

  int i;
  double **Mv;
  Mv=alocamd(img->width, img->height); 

  IplImage *imgHSV;         // Image initiale en HSV
  IplImage *imgHSVTat;         // Image tatouée en HSV
  IplImage *imgTat;           // Image tatouée en RGB
  imgHSV=cvCreateImage(cvGetSize(img),img->depth,img->nChannels) ; 
  imgHSVTat=cvCreateImage(cvGetSize(img),img->depth,img->nChannels) ;
  imgTat=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);

  
  cvCvtColor(img,imgHSV,CV_BGR2HSV); // On met dans imgHSV l'image sources e
  extractionCanalV(Mv,imgHSV);
  generationPar(N,img,Logo);
  selection(Mv,N,img);

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
    extractionBloc ( Mv, posx[i], posy[i],N, bloc);      // Extraction des blocs
    dct2dim (bloc, blocT,N,N);              // DCT sur le bloc sélectionné
    insertionMarque(blocT,N,key[i],mes);      // Insertion du message et validation de l'insertion
    dct2dim_inv (blocT, bloc,N,N);          // DCT inverse sur le bloc tatoué
    insertionBloc (bloc, posx[i],posy[i],N,Mv); // Insertion du bloc tatoué dans la matrice de l'image
  }

  fclose(POS);
  fclose(Mark);

  matToImg(Mv,imgHSV,imgHSVTat); // Création de l'image tatouée à partir de Mv et de l'image source
  cvCvtColor(imgHSVTat,imgTat,CV_HSV2BGR); // On convertit l'image HSV tatouée en image RGB
  cvNamedWindow("Image tatouée",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image tatouée",imgTat);
  cvSaveImage ("imageTatouee.jpg", imgTat, p);

  calculPSNR(img);

  cvReleaseImage(&imgTat);
  cvReleaseImage(&imgHSV);
  cvReleaseImage(&imgHSVTat);

}

