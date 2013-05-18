#ifndef LOGOMARK_H
#define LOGOMARK_H

#include <stdio.h>
#include <stdlib.h>
#include <highgui.h>
#include <cv.h>

#include "matrix.h"
#include "global.h"

void markToLogo (IplImage *Logo);
void logoToBin (IplImage *Logo);

#endif
