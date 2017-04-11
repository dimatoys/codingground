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

	TCamera Camera;
public:

	Test2(unsigned int width,
		  unsigned int height,
		  TColor& bgcolor,
		  double camx,
		  double camy,
		  double camz,
		  double camax,
		  double camay,
		  double cams,
		  double camareax,
		  double camareay) :
		Image(width, height),
		Camera(camx, camy, camz, camax, camay, cams, camareax, camareay) {

		Image.DrawRect(0, 0, Image.Width, Image.Height, bgcolor);
	}

	bool Draw3D(double x, double y, double z, TColor& color) {
		double cx,cy;
		Camera.GetCameraPixel(x, y, z, cx, cy);
		int dx = cx * Image.Width;
		int dy = cy * Image.Height;
		if ((dx >= 0) && (dy >= 0) && (dx < Image.Width) && (dy < Image.Height)) {
			Image.DrawPixel(dx, dy, color);
			return true;
		} else {
			return false;
		}
	}

	void DrawNet(TColor& color) {
		for (double y = 0.0; y <= 90.0; y += 10.0) {
			for (double x = 0.0; x < 1000.0; x += 2.5) {
				if (Draw3D(x, y, 0, color)) {
					Draw3D(-x, y, 0, color);
					Draw3D(x, -y, 0, color);
					Draw3D(-x, -y, 0, color);

					Draw3D(y, x, 0, color);
					Draw3D(-y, x, 0, color);
					Draw3D(y, -x, 0, color);
					Draw3D(-y, -x, 0, color);
				} else {
					printf("out: (%f,%f)\n", x, y);
					break;
				}
			}
		}
	}

	void PosTest() {
		double ax, ay, cx, cy;
		double pos = 1000.0;
		Camera.GetCameraAngles(pos, 0, 0, ax, ay);
		Camera.GetCameraPixel(pos, 0, 0, cx, cy);
		printf("ax=%f (%f)\n cx=%f\n", ax * 180.0 / M_PI, ax / (M_PI / 2.0) , cx);
	}

	void Save(const char* fileName) {
		Image.SaveBMP(fileName);
	}
};

int main () {

	TColor bgcolor = {200, 200, 200};
	TColor fgcolor = {0, 0, 0};

	Test2 test2(600, 600, bgcolor,
			    100, 0, 50,
				M_PI * 0.25, 0, M_PI / 5,
				M_PI * 0.9, M_PI * 0.9);

	test2.DrawNet(fgcolor);
	test2.Save("test2.bmp");

	//test2.PosTest();

    return 0;
}
