#include "detection.h"

void detectionMarque(int N){

  int i,j;
  int x,y;
  double proj;
  double aux;
  float Q;
  int mes_dec,m;
  double key_i;
  int echec=0;
  double **blc;
  double **blcT;
  IplImage *imgDet;
  double **Mtest;
  IplImage *imgTat;
  int cpt=0;

  blc=alocamd(N,N);
  blcT=alocamd(N,N);

  imgTat=cvLoadImage("Resultat/imageTatouee.jpg",1);
  Mtest=alocamd(imgTat->width,imgTat->height);
  imgDet=cvCreateImage(cvGetSize(imgTat),imgTat->depth,imgTat->nChannels);

  cvCvtColor(imgTat,imgDet,CV_BGR2HSV);
  extractionCanalV(Mtest,imgDet);


  if ((POS=fopen("Resultat/position_bloc.txt","r"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }

  if ((KEY=fopen("Resultat/key.txt","r"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }

  if ((Mark=fopen("Resultat/Marque.txt","r"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }

  if ((MarkDet=fopen("Resultat/MarqueDetectee.txt","w"))==NULL){
    printf("Erreur ouverture fichier.\n");
    exit (EXIT_FAILURE);
  }

  while(cpt<NWB){

    fscanf(POS,"%d %d\n",&x,&y);

    extractionBloc(Mtest,x,y,N,blc);
    dct2dim (blc, blcT,N,N);

    fscanf(KEY,"%lf\n",&key_i);

    proj=0;
    for(i=0;i<N;i++){
      for(j=0;j<N;j++){
      
	proj+=blcT[i][j]*masque_t[i][j]/Norme_masque;
      }
    }
    aux=floor((proj-pas*key_i)/(pas)+0.5);
    Q = aux*pas-(proj-pas*key_i);
 
    if (fabs(Q)<(1-a)*pas/2)
      mes_dec=0;
    else
      mes_dec=1;

    fprintf(MarkDet,"%d\n",mes_dec);
    fscanf(Mark,"%d\n",&m);

    if (mes_dec!=m)
      echec++;
    cpt++;
  }
  printf("%'.2f%% des blocs marqués n'ont pas été détectés.\n",((float)echec/NWB)*100);

  fclose(MarkDet);
  markToLogo(Logo);

  dalocd(blc,N);
  dalocd(blcT,N);
  fclose(KEY);
  fclose(POS);
  fclose(Mark);

}
