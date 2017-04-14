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
	const static int SmoothingMatrixSize = 10;

	double SmoothingMatrix[SmoothingMatrixSize][SmoothingMatrixSize];
	double ProductionMatrix[SmoothingMatrixSize - 2][SmoothingMatrixSize];

public:
	void CountSmoothingMatrix(double s);
	void CountProductionMatrix(double s);
	void Smoothing(TImage<TColor>& src, TImage<TDColor>& dst, int k);
	void ToRGB(TImage<TDColor>& img, TRGBImage& rgb);

	void CountProduction(TImage<TDColor>& src, TImage<TGradientColor>& dst);
	void CountSmoothProduction(TImage<TColor>& src, TImage<TGradientColor>& dst, int k);
	void CountSmoothProductionModule(TImage<TColor>& src, TImage<TDColor>& dst, int k);
	void CountMod(TImage<TGradientColor>& src, TImage<TDColor>& dst);

	double CountDiff(TGradientColor& p1, TGradientColor& p2);

	double DumpDiffStat(TImage<TGradientColor>& grad, int k);

	void FindUniqs(TImage<TColor>& img, TImage<TDColor>& grad, unsigned int area);

	double CountDistinction(unsigned int x, unsigned int y, int prodShift,
			                TImage<TColor>& img, TImage<TDColor>& grad,
							unsigned int area);

	double CountDiff(TColor& color1, TDColor& grad1,
			         TColor& color2, TDColor& grad2,
	                 double prodWeight);
};



#endif /* EXTRACTOR_H_ */
