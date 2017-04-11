/*
 * test4.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Dmitry ryashchentsev
 */

#include "bmp.h"
#include "extractor.h"

#include <iostream>

int main() {

	TRGBImage src("bridge.bmp");
	TImage<double> dst(src.Width, src.Height, src.Depth * 2);

	TProduction prod;
	prod.SetR(2);
	//prod.CountProduction(src, dst);

	std::cout << "rec=" << sizeof(TDistance) << " int=" << sizeof(int) << " double=" << sizeof(double) << std::endl;

	return 0;
}
