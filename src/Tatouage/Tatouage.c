#include <stdio.h> 
#include <highgui.h>
#include <cv.h>


#include "global.h"
#include "fonctions.h"
#include "insertion.h"
#include "detection.h"
#include "matrix.h"

int main (int argc, char **argv){

	a = strtof(argv[4], NULL)/100;
	pas = strtof(argv[5], NULL)/100;

	int N=4; //définition de la taille des blocs pour la DCT

	int p[3];  
	p[0]=CV_IMWRITE_JPEG_QUALITY;
	p[1]=100;
	p[2]=0;


	bloc=alocamd(N,N);                     // Allocation des blocs
	blocT=alocamd(N,N);                    // Allocation des blocs transformés    

	if (strcmp(argv[3],"insertion") == 0)
	{
		/** Génération de la clef, de la marque, insertion du tatouage et enregistrement de l'image tatouée **/

		chargerImage(argv[1]);
		chargerLogo(argc,argv[2]);
		NWB=(Logo->width)*(Logo->height);
		cvNamedWindow("Image source",CV_WINDOW_AUTOSIZE);
		cvShowImage ("Image source",img); // affiche de imgHSV
		Insertion (img, N, p);
	}
	else if (strcmp(argv[3],"detection") == 0)
	{
		/** Détection de la marque et récupération du logo **/
		chargerImage(argv[1]);
		chargerLogo(argc,argv[2]);
		NWB=(Logo->width)*(Logo->height);
		detectionMarque(N);  //Détection des blocs marqués
	}
	else if (strcmp(argv[3],"attaquer") == 0)
	{
		chargerImage(argv[1]);
		p[1] = strtof(argv[6], NULL)/100;
		cvSaveImage ("Resultat/imageTatouee.jpg", img, p);
	}

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
