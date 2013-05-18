#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>

int main (int argc, char **argv){

  IplImage *source;
  source=cvLoadImage(argv[1],1);

  int p[3];  
  p[0]=CV_IMWRITE_JPEG_QUALITY;
  p[1]=100;
  p[2]=0;

  cvSaveImage(argv[2],source,p);

  return EXIT_SUCCESS;
}
  
