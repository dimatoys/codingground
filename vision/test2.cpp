/*
 * test2.cpp
 *
 *  Created on: Apr 5, 2017
 *      Author: Dmitry Ryashchentsev
 */

#include "bmp.h"
#include "camera.h"

#include <math.h>
#include <stdio.h>

class Test2 {
	TRGBImage Image;
	unsigned char* Color;

	TCamera Camera;
public:

	Test2(unsigned int width,
		  unsigned int height,
		  unsigned char* fgcolor,
		  unsigned char* bgcolor,
		  double camx,
		  double camy,
		  double camz,
		  double camax,
		  double camay,
		  double cams,
		  double camareax,
		  double camareay) :
		Image(width, height),
		Camera(camx, camy, camz, camax,camay, cams, camareax, camareay) {

		Color = fgcolor;
		Image.DrawRect(0, 0, Image.Width, Image.Height, bgcolor);
	}

	bool Draw3D(double x, double y, double z) {
		double cx,cy;
		Camera.GetCameraPixel(x, y, z, cx, cy);
		int dx = cx * Image.Width;
		int dy = cy * Image.Height;
		if ((dx >= 0) && (dy >= 0) && (dx < Image.Width) && (dy < Image.Height)) {
			Image.DrawPixel(dx, dy, Color);
			return true;
		} else {
			return false;
		}
	}

	void DrawNet() {
		for (double y = 0.0; y <= 90.0; y += 10.0) {
			for (double x = 0.0; x < 1000.0; x += 2.5) {
				if (Draw3D(x, y, 0)) {
					//Draw3D(-x, y, 0);
					//Draw3D(x, -y, 0);
					//Draw3D(-x, -y, 0);
				} else {
					printf("out: (%f,%f)\n", x, y);
					break;
				}
			}
		}
	}

	void Save(const char* fileName) {
		Image.SaveBMP(fileName);
	}
};

int main () {

	unsigned char bgcolor[] = {200, 200, 200};
	unsigned char fgcolor[] = {0, 0, 0};

	Test2 test2(600, 600, fgcolor, bgcolor, 0, 0, 50, 0, 0, 0, M_PI * 0.9, M_PI * 0.5);
	test2.DrawNet();

	test2.Save("test2.bmp");
    return 0;
}
