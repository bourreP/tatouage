#include <stdio.h> 
#include "matrix.h"
#include <highgui.h>//<opencv/highgui.h>
#include <cv.h>//<opencv/cv.h>
#include "global.h"
#include "fonctions.h"
#include "insertion.h"
#include "detection.h"

int main (int argc, char **argv){

  chargerImage(argv[1]);
  chargerLogo(argc,argv[2]);

  int N=4; //définition de la taille des blocs pour la DCT
  a=0.68;
  pas=110;
  NWB=(Logo->width)*(Logo->height);
  
  int p[3];  
  p[0]=CV_IMWRITE_JPEG_QUALITY;
  p[1]=100;
  p[2]=0;
 
  cvNamedWindow("Image source",CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image source",img); // affiche de imgHSV
  
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
