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
	TImage<TVector2D> dst(src.Width, src.Height);

	TProduction prod;
	prod.SetR(2);
	prod.CountProduction(src, dst);

	return 0;
}
