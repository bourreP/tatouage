#include <stdio.h>
#include <stdlib.h>
#include <highgui.h>//<opencv/highgui.h>
#include <cv.h>//<opencv/cv.h>
#include "matrix.h"
#include "dct.h"
#include "fonctions.h"
#include "global.h"

int main (int argc, char **argv){

  int N=4; //définition de la taille des blocs pour la DCT
  int i,j;
  CvScalar s;
  double **Mv;               // Matrice initiale du canal V de l'image HSV 
  IplImage *img;            // Image initiale en  RGB
  IplImage *imgHSV;         // Image initiale en HSV
  IplImage *imgHSVTat;         // Image tatouée en HSV
  IplImage *imgTat;           // Image tatouée en RGB
  a=0.6;
  pas=10;
  NWB=20;
  if (argv[1] != NULL)
  {
	  img=cvLoadImage(argv[1],3);
  }
  else
  {
	  img=cvLoadImage("../Images/lena.jpg",3);
  }
  cvNamedWindow("Image source HSV",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image source HSV",img); // affiche de imgHSV
      
  imgHSV=cvCreateImage(cvGetSize(img),img->depth,img->nChannels) ; 
  imgHSVTat=cvCreateImage(cvGetSize(img),img->depth,img->nChannels) ;
  imgTat=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
  srand(time(NULL));
  
  posx=alocavi(NWB);
  for(i=0;i<NWB;i++)
	posx [i] = N*(rand()%((img->width)/N));

  posy=alocavi(NWB);
  for(i=0;i<NWB;i++)
	posy[i] = N*(rand()%((img->height)/N));
  
  key=alocavd(NWB);
  for(i=0;i<NWB;i++)
	key[i]=rand()/((double)MAX_INT);
  
  mes=alocavi(NWB);
  for(i=0;i<NWB;i++)
	mes[i]=rand()%2;

  if ((POS=fopen("position_bloc.txt","w"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }
  for (i=0;i<NWB;i++)
  fprintf(POS,"%d %d\n",posx[i],posy[i]);
  fclose (POS);

  if ((KEY=fopen("key.txt","w"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }
  for (i=0;i<NWB;i++)
  fprintf(KEY,"%f\n",key[i]);
  fclose (KEY);
  if ((Mark=fopen("Marque.txt","w"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }

  for (i=0;i<NWB;i++)
  fprintf(Mark,"%d\n",mes[i]);
  cvNamedWindow("Image source",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image source",img);

  /**     Conversion de l'image RGB en HSV        **/
 
  cvCvtColor(img,imgHSV,CV_BGR2HSV); // On met dans imgHSV l'image sources en HSV
  cvNamedWindow("Image source HSV",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image source HSV",imgHSV); // affiche de imgHSV
      
  /**    On extrait le canal V     **/
 
  Mv=alocamd(img->width, img->height); // Allocation de Mv
  extractionCanalV(Mv,imgHSV, N);
  bloc=alocamd(N,N);                     // Allocation des blocs
  blocT=alocamd(N,N);                    // Allocation des blocs transformés
  for (i=0;i<NWB;i++)
  {
  extractionBloc ( Mv, posx[i], posy[i],N, bloc);      // Extraction des blocs
  dct2dim (bloc, blocT,N,N);              // DCT sur le bloc sélectionné
  insertion (blocT,N,pas,a,key[i],mes[i]);      // Insertion du message et validation de l'insertion
  dct2dim_inv (blocT, bloc,N,N);          // DCT inverse sur le bloc tatoué
  insertionBloc (bloc, posx[i],posy[i],N,Mv); // Insertion du bloc tatoué dans la matrice de l'image

  }


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
  cvSaveImage ("imageTatouee.jpg", imgTat, NULL);
  cvDestroyAllWindows();
  cvReleaseImage(&img);
  cvReleaseImage(&imgTat);
  cvReleaseImage(&imgHSV);
  cvReleaseImage(&imgTat);
  dalocd(bloc,N);
  dalocd(blocT,N);
  freevi(mes);
  freevi(posx);
  freevi(posy);
  freevd(key);
  

  return EXIT_SUCCESS;

}
