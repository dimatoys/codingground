/*
 * camera.cpp
 *
 *  Created on: Apr 5, 2017
 *      Author: Dmitry Ryashchentsev
 */

#include "camera.h"

#include <math.h>

void TCamera::SetS(double s) {
	S = s;
}

void TCamera::GetCameraAngles(double x, double y, double z,
                              double& ax, double& ay) {
	z = Z - z;
	x -= X;
	y -= Y;
	double distance = sqrt(x * x + y * y + z * z);
	double nx = asin(x / distance) + AX;
	double ny = asin(y / distance) + AY;
	ax = nx;
	ay = ny;
}

void TCamera::GetCameraPixel(double x, double y, double z,
                             double& cx, double& cy) {
	double ax,ay;
	GetCameraAngles(x, y, z, ax, ay);
	cx = ax / AreaX + 0.5;
	cy = ay / AreaY + 0.5;
}


