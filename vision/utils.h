/*
 * utils.h
 *
 *  Created on: Apr 11, 2017
 *      Author: Dmitry Ryashchentsev
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "string.h"

template <class T>
class TImage {
protected:
	T* Data;
public:
	unsigned int Width;
	unsigned int Height;

	TImage() {
		Data = (T*)0;
	}

	TImage(unsigned int width,
		   unsigned int height) {

		Data = (T*)0;
		Allocate(width, height);
	}

	void Allocate(unsigned int width,
			      unsigned int height) {
		if (Data != (T*)0) {
			if ((Width == width) && (Height == height)) {
				return;
			}
			delete Data;
		}
		Data = new T[width * height];
		Width = width;
		Height = height;
	}

	T* Cell(int x, int y) {
		return Data + y * Width + x;
	}

	void DrawPixel(int x, int y, const T* color) {
		memcpy(Cell(x, y), color, sizeof(T));
	}

	void DrawRect(int startx, int starty, int width, int height, const T* color) {
		int endx = startx + width;
		int endy = starty + height;
		for (int y = starty; y < endy; ++y) {
			for (int x = startx; x < endx; ++x) {
				DrawPixel(x, y, color);
			}
		}
	}

	~TImage() {
		if (Data != (T*)0) {
			delete Data;
		}
	}
};

typedef unsigned char TColor[3];

void dumpBin(void* ptr, int size);

#endif /* UTILS_H_ */
