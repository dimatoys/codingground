/*
 * extractor.h
 *
 *  Created on: Apr 11, 2017
 *      Author: Dmitry ryashchentsev
 */

#ifndef EXTRACTOR_H_
#define EXTRACTOR_H_

#include "bmp.h"
#include "utils.h"

#include <math.h>
#include <vector>

struct TDistance {
	int A;
	int B;
	double D;

	TDistance(int a, int b) {
		A = a;
		B = b;
		D = sqrt(a * a + b * b);
	}

	void operator = (const TDistance& other) {
		A = other.A;
		B = other.B;
		D = other.D;
	}
};

typedef double TDColor[3];

struct TVector2D {
	double X;
	double Y;
};

typedef TVector2D TGradientColor[3];

class TProduction {
	const static int SmoothingMatixSize = 10;

	double SmoothingMatrix[SmoothingMatixSize][SmoothingMatixSize];
public:
	void CountSmoothingMatrix(double s);
	void Smoothing(TImage<TColor>& src, TImage<TDColor>& dst, int k);
	void ToRGB(TImage<TDColor>& img, TRGBImage& rgb);

	void CountProduction(TImage<TColor>& src, TImage<TGradientColor>& dst);
};



#endif /* EXTRACTOR_H_ */
