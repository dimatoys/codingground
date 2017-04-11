/*
 * extractor.h
 *
 *  Created on: Apr 11, 2017
 *      Author: Dmitry ryashchentsev
 */

#ifndef EXTRACTOR_H_
#define EXTRACTOR_H_

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

class TProduction {
	std::vector<TDistance> Matrix;
public:
	void SetR(double r);

	void CountProduction(TImage<unsigned char> src, TImage<double> dst);
};



#endif /* EXTRACTOR_H_ */
