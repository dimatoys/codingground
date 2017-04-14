/*
 * extractor.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Dmitry Ryashchentsev
 */

#include "extractor.h"

#include <list>

#include <stdio.h>

void TProduction::CountSmoothingMatrix(double s) {

	double d = s * s * 2.0;
	for (int y = 1; y < SmoothingMatrixSize; y++) {
		for (int x = 0; x <= y; x++) {
			SmoothingMatrix[x][y] = exp(-(x * x + y * y) / d);
			SmoothingMatrix[y][x] = SmoothingMatrix[x][y];
		}
	}
}

void TProduction::CountProductionMatrix(double s) {

	CountSmoothingMatrix(s);
	SmoothingMatrix[0][0] = 1.0;
/*
	for (int y = 0; y < SmoothingMatrixSize; y++) {
		for (int x = 0; x < SmoothingMatrixSize; x++) {
			printf(" %5.2f", SmoothingMatrix[x][y]);
		}
		printf("\n");
	}

	printf("\n");
*/
	for (int y = 0; y < SmoothingMatrixSize; y++) {
		for (int x = 0; x < SmoothingMatrixSize - 2; x++) {
			ProductionMatrix[x][y] = SmoothingMatrix[x][y] - SmoothingMatrix[x + 2][y];
			//printf(" %5.2f", SmoothingMatrix[x][y] - SmoothingMatrix[x + 2][y]);
		}
		//printf("\n");
	}

}

void TProduction::Smoothing(TImage<TColor>& src, TImage<TDColor>& dst, int k) {

	dst.Allocate(src.Width - 2 * k, src.Height - 2 * k);

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
				(*dst.Cell(x - k, y - k))[p] = v;
			}
		}
	}
}

void TProduction::ToRGB(TImage<TDColor>& img, TRGBImage& rgb) {
	double min = 1e20;
	double max = -1;

	rgb.Allocate(img.Width, img.Height);

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

void TProduction::CountProduction(TImage<TDColor>& src, TImage<TGradientColor>& dst) {
	dst.Allocate(src.Width - 2, src.Height - 2);
	for (unsigned int y = 1; y < src.Height - 1; ++y) {
		for (unsigned int x = 1; x < src.Width - 1; ++x) {
			TGradientColor* pixel = dst.Cell(x - 1, y - 1);
			for (int p = 0; p < sizeof(TColor); ++p) {
				(*pixel)[p].X = (*src.Cell(x + 1, y))[p] - (*src.Cell(x - 1, y))[p];
				(*pixel)[p].Y = (*src.Cell(x, y + 1))[p] - (*src.Cell(x, y - 1))[p];
			}
		}
	}
}

void TProduction::CountSmoothProduction(TImage<TColor>& src, TImage<TGradientColor>& dst, int k) {
	dst.Allocate(src.Width - 2 * k, src.Height - 2 * k);
	for (unsigned int y = k; y < src.Height - k; ++y) {
		for (unsigned int x = k; x < src.Width - k; ++x) {
			for (int p = 0; p < sizeof(TColor); ++p) {
				double vx = 0;
				double vy = 0;
				for (int i = 0; i < k; i++) {
					vx += ProductionMatrix[i][0] * ((*src.Cell(x + i + 1, y))[p] - (double)(*src.Cell(x - i - 1, y))[p]);
					vy += ProductionMatrix[i][0] * ((*src.Cell(x, y + i + 1))[p] - (double)(*src.Cell(x, y - i - 1))[p]);
					for (int j = 1; j < k; j++) {
						vx += ProductionMatrix[i][j] * ((*src.Cell(x + i + 1, y + j))[p] - (double)(*src.Cell(x - i - 1, y + j))[p] +
													    (*src.Cell(x + i + 1, y - j))[p] - (*src.Cell(x - i - 1, y - j))[p]);
						vy += ProductionMatrix[i][j] * ((*src.Cell(x + j, y + i + 1))[p] - (double)(*src.Cell(x + j, y  - i - 1))[p] +
													    (*src.Cell(x - j, y + i + 1))[p] - (*src.Cell(x - j, y - i - 1))[p]);
					}
				}
				(*dst.Cell(x - k, y - k))[p].X = vx;
				(*dst.Cell(x - k, y - k))[p].Y = vy;
			}
		}
	}
}

void TProduction::CountSmoothProductionModule(TImage<TColor>& src, TImage<TDColor>& dst, int k) {
	dst.Allocate(src.Width - 2 * k, src.Height - 2 * k);
	for (unsigned int y = k; y < src.Height - k; ++y) {
		for (unsigned int x = k; x < src.Width - k; ++x) {
			for (int p = 0; p < sizeof(TColor); ++p) {
				double vx = 0;
				double vy = 0;
				for (int i = 0; i < k; i++) {
					vx += ProductionMatrix[i][0] * ((*src.Cell(x + i + 1, y))[p] - (double)(*src.Cell(x - i - 1, y))[p]);
					vy += ProductionMatrix[i][0] * ((*src.Cell(x, y + i + 1))[p] - (double)(*src.Cell(x, y - i - 1))[p]);
					for (int j = 1; j < k; j++) {
						vx += ProductionMatrix[i][j] * ((*src.Cell(x + i + 1, y + j))[p] - (double)(*src.Cell(x - i - 1, y + j))[p] +
													    (*src.Cell(x + i + 1, y - j))[p] - (*src.Cell(x - i - 1, y - j))[p]);
						vy += ProductionMatrix[i][j] * ((*src.Cell(x + j, y + i + 1))[p] - (double)(*src.Cell(x + j, y  - i - 1))[p] +
													    (*src.Cell(x - j, y + i + 1))[p] - (*src.Cell(x - j, y - i - 1))[p]);
					}
				}
				(*dst.Cell(x - k, y - k))[p] = sqrt(vx * vx + vy * vy);
			}
		}
	}
}

double TProduction::CountDiff(TGradientColor& p1, TGradientColor& p2) {
	double d = 0;
	for (int i = 0; i < sizeof(TColor); ++i) {
		double dx = p1[i].X - p2[i].X;
		double dy = p1[i].Y - p2[i].Y;
		d += dx * dx + dy * dy;
	}
	return sqrt(d);
}

double TProduction::DumpDiffStat(TImage<TGradientColor>& grad, int k) {
	std::list<double> distances;

	for (unsigned int y = 1; y < grad.Height; ++y) {
		for (unsigned int x = 0; x < grad.Width; ++x) {
			double d = CountDiff(*grad.Cell(x, y), *grad.Cell(x, y - 1));
			distances.push_back(d);
		}
	}

	for (unsigned int y = 0; y < grad.Height; ++y) {
		for (unsigned int x = 1; x < grad.Width; ++x) {
			double d = CountDiff(*grad.Cell(x, y), *grad.Cell(x - 1, y));
			distances.push_back(d);
		}
	}

	distances.sort();

	double min = distances.front();
	double max = distances.back();
	int size = distances.size();
	double stepVal = (max - min) / k;
	int stepMass = size / k;

	double endVal = min + stepVal;
	int countMass = 0;
	printf("min=%f max=%f size=%d\n", min, max, size);
	std::list<double>::const_iterator itVal = distances.begin();
	std::list<double>::const_iterator itMass = distances.begin();
	for (int i = 1; i <= k; i++) {
		int count = 0;
		while((itVal != distances.end()) && (*itVal < endVal)) {
			++count;
			++itVal;
		}

		for (int j = 0; j < stepMass; ++j) {
			++itMass;
		}
		countMass += stepMass;

		printf("%10.1f: %10d     %10d: %12.7f\n", endVal, count, countMass, *itMass);
		endVal += stepVal;
	}
}

void TProduction::CountMod(TImage<TGradientColor>& src, TImage<TDColor>& dst) {
	dst.Allocate(src.Width, src.Height);
	for (unsigned int y = 0; y < src.Height; ++y) {
		for (unsigned int x = 0; x < src.Width; ++x) {
			TGradientColor* gradient = src.Cell(x, y);
			TDColor* color = dst.Cell(x, y);
			for (int p = 0; p < sizeof(TColor); ++p) {
				(*color)[p] = sqrt((*gradient)[p].X * (*gradient)[p].X + (*gradient)[p].Y * (*gradient)[p].Y);
			}
		}
	}
}

void TProduction::FindUniqs(TImage<TColor>& img, TImage<TDColor>& grad, unsigned int area) {
	unsigned int k = (img.Width - grad.Width) / 2;
	printf("k=%d\n", k);
}

double TProduction::CountDistinction(unsigned int x, unsigned int y, int prodShift,
		                             TImage<TColor>& img, TImage<TDColor>& grad,
								     unsigned int area) {
	return 0.0;
}

double TProduction::CountDiff(TColor& color1, TDColor& grad1,
		                      TColor& color2, TDColor& grad2,
							  double prodWeight) {
	double c0 = color1[0] - (double)color2[0];
	double c1 = color1[1] - (double)color2[1];
	double c2 = color1[2] - (double)color2[2];
	double g0 = grad1[0] - grad2[0];
	double g1 = grad1[1] - grad2[1];
	double g2 = grad1[2] - grad2[2];

	return sqrt(c0 * c0 + c1 * c1 + c2 * c2 + (g0 * g0 + g1 * g1 + g2 * g2) * prodWeight);
}
