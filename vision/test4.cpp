/*
 * test4.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Dmitry Ryashchentsev
 */

#include "bmp.h"
#include "extractor.h"

#include <iostream>

int main() {

	TRGBImage src("bridge.bmp");
	TImage<TDColor> dst(src.Width, src.Height);
	TRGBImage rgb(src.Width, src.Height);

	TProduction prod;
	prod.CountSmoothingMatrix(1.4);
	prod.Smoothing(src, dst, 3);
	prod.ToRGB(dst, rgb);
	rgb.SaveBMP("bridge3.bmp");

	return 0;
}
