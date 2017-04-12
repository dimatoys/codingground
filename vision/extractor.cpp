/*
 * extractor.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Dmitry Ryashchentsev
 */

#include "extractor.h"

#include <stdio.h>

void TProduction::CountSmoothingMatrix(double s) {

	double d = s * s * 2.0;
	for (int i = 1; i < SmoothingMatixSize; i++) {
		for (int j = 0; j <= i; j++) {
			SmoothingMatrix[i][j] = exp(-(i * i + j * j) / d);
			SmoothingMatrix[j][i] = SmoothingMatrix[i][j];
		}
	}
/*
	for (int i = 0; i < SmoothingMatixSize; i++) {
		for (int j = 0; j < SmoothingMatixSize; j++) {
			printf(" %5.2f", SmoothingMatrix[i][j]);
		}
		printf("\n");
	}
*/
}

void TProduction::Smoothing(TImage<TColor>& src, TImage<TDColor>& dst, int k) {
	for (unsigned int y = k; y < src.Height - k; ++y) {
		for (unsigned int x = k; x < src.Width - k; ++x) {
			for (int p = 0; p < sizeof(TColor); ++p) {
				double v = (*src.Cell(x, y))[p];
				for (int i = 1; i <= k; i++) {
					for (int j = 0; j <= k; j++) {
						v += (*src.Cell(x + j, y + i))[p] * SmoothingMatrix[i][j];
						v += (*src.Cell(x + j, y - i))[p] * SmoothingMatrix[i][j];
						v += (*src.Cell(x - j, y + i))[p] * SmoothingMatrix[i][j];
						v += (*src.Cell(x - j, y - i))[p] * SmoothingMatrix[i][j];
					}
				}
				(*dst.Cell(x, y))[p] = v;
			}
		}
	}
}

void TProduction::ToRGB(TImage<TDColor>& img, TRGBImage& rgb) {
	double min = 1e20;
	double max = -1;
	for (unsigned int y = 0; y < img.Height; ++y) {
		for (unsigned int x = 0; x < img.Width; ++x) {
			for (int p = 0; p < sizeof(TColor); ++p) {
				double v = (*img.Cell(x, y))[p];
				if (v > max) {
					max = v;
				}
				if (v < min) {
					min = v;
				}
			}
		}
	}
	for (unsigned int y = 0; y < img.Height; ++y) {
		for (unsigned int x = 0; x < img.Width; ++x) {
			for (int p = 0; p < sizeof(TColor); ++p) {
				double v = (*img.Cell(x, y))[p];
				(*rgb.Cell(x, y))[p] = (unsigned char) (0xFF * (v - min) / (max - min));
			}
		}
	}
}

void TProduction::CountProduction(TImage<TColor>& src, TImage<TGradientColor>& dst) {
}



