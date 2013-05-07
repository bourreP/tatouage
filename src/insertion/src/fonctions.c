#include <stdio.h> 
#include "matrix.h"
#include <math.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include "dct.h"


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


void extractionCanalV (double **Mat, IplImage *imgHSV, int N) {

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

void insertion ( double **blocT, int N, int pas, float a,double key,int mes){

  int i,j;
  float proj=0;
  float proj2=0;
  float q,Q;
  float deux =2;
  float w;
  float masque_t[4][4]= {
    {-0.3028,0.0325,0.3375,0.0162},
    {0.0325,1.5282,21.8675,0.7641},
    {0.3375,21.8675,30.8715,10.9337},
    {0.0162,0.7641,10.9337,0.3821}
  };
  float Norme_masque=44.8071;
  int mes2;
  double **blocT2;
  float aux;
  blocT2=alocamd(N,N);

  for (i=0;i<N;i++){                // Copie de blocT dans blocT2
    for (j=0;j<N;j++){
      blocT2[i][j]=blocT[i][j];
      //      printf("%f ", blocT2[i][j]);
    }
    //    printf("\n");
  }
  //  printf("\n");

  for (i=0;i<N;i++){               // Transposée de blocT
    for(j=0;j<N;j++){

      aux=blocT[i][j];
      blocT[i][j]=blocT[j][i];
      blocT[j][i]=aux;
      //      printf("%f ",blocT[i][j]); 
    }
    //    printf("\n");
  }
  //  printf("\n");

  for (i=0;i<N;i++){
    for (j=0;j<N;j++){
      proj+=blocT[i][j]*masque_t[i][j]/Norme_masque; // Calcul du projeté de la matrice sur le masque
    }
  }
  //  printf("%f\n", proj);

  q=pas*floor((proj - pas*((float)mes/deux + key))/pas) - (proj - (pas*((float)mes/deux + key)));
  //  printf("%f\n\n",q);
  w=proj + a*q;
  //  printf("%f\n\n",w);
 
  for (i=0;i<N;i++){
    for (j=0;j<N;j++){
      blocT[i][j]= blocT2[i][j]+(w*masque_t[i][j]/Norme_masque); // Remplacement de la matrice B par la matrice marquée
      //   printf("%f ",blocT[i][j]);
    }
    //    printf("\n");
  }
  dalocd(blocT2,N);

  /** Test sur la réussite de l'insertion **/

  for (i=0;i<N;i++){        // Projection du bloc tatoué sur le masque
    for (j=0;j<N;j++){
      proj2+=blocT[i][j]*masque_t[i][j]/Norme_masque; 
    }
  }
  //  printf("%f\n",proj2);

  Q=pas*(floor((proj2-key*pas)/pas))-proj2+(key*pas); // Variable de détection
  if (Q<0)
    Q= (-Q);
  printf("%f\n",Q);

  if (Q < ((1-a)*(pas/deux))){  // Critère de détection
    mes2=0;
  }
  else{
    mes2=1;
  }
  printf("Message test : %d\n",mes2);
  if (mes!=mes2){
    printf("L'insertion à échouée.\n");
    exit (EXIT_FAILURE);
  }
  else{
    printf("L'insertion à réussie.\n");
  }
}