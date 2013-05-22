#include <stdio.h> 
#include <highgui.h>
#include <cv.h>

#include "matrix.h"
#include "global.h"
#include "fonctions.h"
#include "insertion.h"
#include "detection.h"

int main (int argc, char **argv){

	printf ("#########################################################################\n");
	printf ("#			TEST DU CHARGEMENT DE L'IMAGE			#\n");
	printf ("#########################################################################\n");
	chargerImage("./source.jpg");
	if (!img)
	{
		printf("Chargement de l'image : Non\n");
		return EXIT_FAILURE;
	}
	else
		printf("#									#\n");
		printf("#			Chargement de l'image : OK			#\n");
		printf("#									#\n");

	printf ("#########################################################################\n");
	printf ("#			TEST DU CHARGEMENT DU LOGO			#\n");
	printf ("#########################################################################\n");
	chargerLogo(2,"./logo.jpg");

	if (!Logo)
	{
		printf("Chargement du logo : Non\n");
		return EXIT_FAILURE;
	}
	else
		printf("#									#\n");
		printf("#			Chargement du logo : OK				#\n");
		printf("#									#\n");

	int N=4; //définition de la taille des blocs pour la DCT
	a=0.72;
	pas=115;
	NWB=(Logo->width)*(Logo->height);

	int p[3];  
	p[0]=CV_IMWRITE_JPEG_QUALITY;
	p[1]=100;
	p[2]=0;

	bloc=alocamd(N,N);                     // Allocation des blocs
	blocT=alocamd(N,N);                    // Allocation des blocs transformés    

	/** Génération de la clef, de la marque, insertion du tatouage et enregistrement de l'image tatouée **/

	Insertion (img, N, p);

	/** Détection de la marque et récupération du logo **/

	detectionMarque(N);  //Détection des blocs marqués

	cvWaitKey(0);
	cvDestroyAllWindows();

	cvReleaseImage(&img);
	cvReleaseImage(&Logo);

	dalocd(bloc,N);
	dalocd(blocT,N);

	freevi(posx);
	freevi(posy);
	freevd(key);  

	return EXIT_SUCCESS;

}
