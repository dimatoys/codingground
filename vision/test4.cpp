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

	TProduction prod;

	prod.CountProductionMatrix(1.4);

	//prod.CountSmoothingMatrix(1.4);

	TRGBImage src("bridge.bmp");

	//TImage<TDColor> smooth;
	//prod.Smoothing(src, smooth, 3);

	//TRGBImage rgbs;
	//prod.ToRGB(dst, rgbs);
	//rgbs.SaveBMP("bridge3.bmp");

	TImage<TGradientColor> grad;
	//prod.CountProduction(smooth, grad);

	prod.CountSmoothProduction(src, grad, 3);

	prod.DumpDiffStat(grad, 30);

	//TImage<TDColor> mod;
	//prod.CountMod(grad, mod);

	//TRGBImage rgbm;
	//prod.ToRGB(mod, rgbm);
	//rgbm.SaveBMP("bridge5.bmp");

	return 0;
}
