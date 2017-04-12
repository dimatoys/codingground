/*
 * extractor.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Dmitry Ryashchentsev
 */

#include "extractor.h"

void TProduction::SetR(double r) {
	TDistance distance1(1, 0);
	Matrix.push_back(distance1);

	TDistance distance2(1, 1);
	Matrix.push_back(distance2);

}

void TProduction::CountProduction(TImage<TColor>& src, TImage<TGradientColor>& dst) {

	for (unsigned int y = 1; y < src.Height - 1; ++y) {
		for (unsigned int x = 1; x < src.Width - 1; ++x) {
			TVector2D* vector = &(*dst.Cell(x, y)[0]);
			for (unsigned int i = 0; i < sizeof(TColor); ++i) {
				double dx = 0;
				double dy = 0;

				for (std::vector<TDistance>::const_iterator it = Matrix.begin(); it != Matrix.end(); ++it) {

				}

				//dx += (src.Cell(x + distance.A, y + distance.B)[i] - src.Cell(x - distance.A, y - distance.B)[i]) / distance.D;
				//dy += (src.Cell(x, y + 1)[i] -src.Cell(x, y - 1)[i]) / 2.0;

				vector->X = dx;
				vector->Y = dy;
				++vector;
			}
		}
	}
}



