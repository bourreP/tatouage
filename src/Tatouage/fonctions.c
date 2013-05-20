#include "fonctions.h"

void echanger ( int *px, int *py ) {

  int aux = *px;

  *px = *py;
  *py = aux;
}

void echangerDouble ( double *x, double *y ) {

  double aux = *x;

  *x = *y;
  *y = aux;
}

void calculPSNR (IplImage *img){

  int i,j;
  double EQMb=0;
  double EQMg=0;
  double EQMr=0;
  double EQM=0;
  double PSNR;
  CvScalar v;
  CvScalar s;
  IplImage *imgTat;
  imgTat= (IplImage* ) cvLoadImage("Resultat/imageTatouee.jpg",1);

  for (i=0;i<img->width;i++)
    for (j=0;j<img->height;j++){
      v=cvGet2D(img,j,i); 
      s=cvGet2D(imgTat,j,i);
      EQMb+=(v.val[0]-s.val[0])*(v.val[0]-s.val[0]);
      EQMg+=(v.val[1]-s.val[1])*(v.val[1]-s.val[1]);
      EQMb+=(v.val[2]-s.val[2])*(v.val[2]-s.val[2]);
    }

  EQM=(EQMb+EQMg+EQMr)/(img->height*img->width*3);
  PSNR=10*log10((255*255)/EQM);

  printf("On a un PSNR de %lfdB.\n",PSNR);
  cvReleaseImage(&imgTat);

}

void triAbulles ( double *t,int *x,int *y,int N ) {

  typedef enum { FAUX, VRAI } Booleen;  
  int i = 0, j;
  Booleen aucunEchange = FAUX;

  while ( ( i<((img->height*img->width)/(N*N*5))-1 ) && !aucunEchange ) {
  
    aucunEchange = VRAI;

    for ( j=((img->height*img->width)/(N*N*5))-1; j>i; j-- )
      if ( t[j]>t[j-1] ) {
	echangerDouble ( &t[j], &t[j-1] );
	echanger(&x[j],&x[j-1]);
	echanger(&y[j],&y[j-1]);
	aucunEchange = FAUX;   
   }
    i++;   
  }
}


void chargerImage (char *image){

  if (image==NULL)
    img= (IplImage*) cvLoadImage("./ImagesTest/source.jpg",1);
  else
    img= (IplImage*) cvLoadImage(image,1);

  if(img->height>2000 || img->height<200 || img->width>2000 || img->width<200){
    printf("Veuillez choisir une image entre 200x200pixels et 2000x2000pixels.\n");
    exit(EXIT_FAILURE);
  }
}

void chargerLogo (int arg, char *logo){

  if (arg<2)
    Logo= (IplImage*) cvLoadImage ("./LogosTest/logo.png",0);
  else
    Logo= (IplImage*) cvLoadImage (logo,0); 

  if(Logo->height<16 || Logo->height>48 || Logo->width<16 ||Logo->width>48){
    printf("Veuillez choisir un logo entre 16x16pixels et 48x48pixels.\n");
    exit(EXIT_FAILURE);
  }
}

/* Conversion d'une matrice en image */

void matToImg (double **Mat, IplImage *imgSRC,IplImage *imgDST ){
  
  int i;
  int j;
  CvScalar v;

  for (i=0; i<imgSRC->width; i++)
    for (j=0; j<imgSRC->height; j++) {
 
      v=cvGet2D(imgSRC,j,i); 
      v.val[2]=Mat[i][j];
      cvSet2D (imgDST,j,i,v); 
    }
}

/**         Extraction d'un bloc         **/

void extractionBloc (double **Mat, int posx, int posy,int N,double **bloc){

  int i;
  int j;
  
  for (i=0; i<N; i++){
    for (j=0; j<N; j++){
 
      bloc[i][j]=Mat[i+posx][j+posy];
    }
  }
}

/** Réinsertion d'un bloc tatoué dans la matrice **/

void insertionBloc ( double **bloc, int posx, int posy, int N, double **Mat ){

  int i,j;

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){

      Mat[posx+i][posy+j]=bloc[i][j];       // Implantation du bloc transformé dans MTr
    }
  }
}

/**        Extraction du canal V          **/


void extractionCanalV (double **Mat, IplImage *imgHSV) {

  int i, j;
  CvScalar s;                // Vecteur qui contiendra les trois canaux de l'image HSV 
  for(i=0; i<imgHSV->width; i++){
    for(j=0; j<imgHSV->height; j++){

      s=cvGet2D(imgHSV,j,i);         // On extrait dans s les 3 canaux de l'image HSV
      Mat[i][j]=s.val[2];              // On extrait dans M le canal V pour la DCT
    }
  }
}

/** Insertion du tatouage **/

void DCT (double **Mat, double **MTr, IplImage *imgHSV,int N){

  int i,j;
  int i0,j0;
  double **blc;            // Bloc de 4x4 de M
  double **blcT;           // Bloc 4x4 de MT, DCT de blocT

  for(i=0; i<(imgHSV->width/N); i++){
    for(j=0; j<(imgHSV->height/N); j++){

      blc=alocamd(N,N);                     // Allocation des blocs
      blcT=alocamd(N,N);                    // Allocation des blocs transformés

      extractionBloc ( Mat, i*N, j*N,N, blc);      // Extraction des blocs
      dct2dim (blc, blcT,N,N);              // Transformation des blocs

      for(i0=0;i0<N;i0++)
	for(j0=0;j0<N;j0++)
	  MTr[N*i+i0][N*j+j0]=blcT[i0][j0];       // Implantation du bloc transformé dans MTr
      dalocd(blc,N);
      dalocd(blcT,N);
    }
  }
}
/*
void DCTinv (double **Mat,double **MTr, double ** MFi, IplImage *imgHSV, IplImage *imgDCT,int N){

  int i,j;
  int i0,j0;
  int k,l;
  CvScalar v;                // Vecteur recevant le canal V de la future image transformée
  double **blc;            // Bloc 4x4 de Mat transformé
  double **blcT;           // Bloc 4x4 de MTr, DCT transformée de M4x4

 
  for(i=0; i<(imgHSV->width/N); i++){
    for(j=0; j<(imgHSV->height/N); j++){
      
      blc=alocamd(N,N);
      blcT=alocamd(N,N);
      extractionBloc ( MTr, i*N, j*N, N, blcT);
      dct2dim_inv (blcT, blc,N,N);
      
      for(i0=0; i0<N; i0++){
	for(j0=0; j0<N; j0++){
	  
	  MFi[N*i+i0][N*j+j0]=blc[i0][j0];
	}
      }

      dalocd (blc,N);
      dalocd (blcT,N);
    }
  }
  
  for (k=0; k<imgHSV->width; k++) {
    for (l=0; l<imgHSV->height; l++) {
 
      v=cvGet2D(imgHSV,l,k); 
      v.val[2]=MFi[k][l];
      cvSet2D (imgHSV,l,k,v); 
    }
  }
}
*/
