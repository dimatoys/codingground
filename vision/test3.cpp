/*
 * test3.cpp
 *
 *  Created on: Apr 10, 2017
 */

#include "bmp.h"

int main () {

	TRGBImage img("bridge.bmp");

	img.SaveBMP("bridge2.bmp");
}



