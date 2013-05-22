#include "fonctions.h"

int calculPSNR (IplImage *img){

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

	if (PSNR < 30)
	{
		printf("Test du PSNR : non\n");
		return EXIT_FAILURE;
	}

	printf ("#########################################################################\n");
	printf ("#				TEST DU PSNR				#\n");
	printf ("#########################################################################\n");
	printf("#									#\n");
	printf("#			Test du PSNR : OK				#\n");
	printf("#									#\n");
	printf("#			Le PSNR vaut : %lfdB			#\n", PSNR);
	printf("#									#\n");
	printf("#		Pour Réussir les tests, il devait être suppérieur à 30dB#\n");
	printf("#									#\n");


	cvReleaseImage(&imgTat);
	return EXIT_SUCCESS;
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

