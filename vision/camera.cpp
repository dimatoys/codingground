/*
 * camera.cpp
 *
 *  Created on: Apr 5, 2017
 *      Author: Dmitry Ryashchentsev
 */

#include "camera.h"

#include <math.h>

void TCamera::GetCameraAngles(double x, double y, double z,
                              double& ax, double& ay) {
	ax = atan(x / Z);
	ay = atan(y / Z);
}

void TCamera::GetCameraPixel(double x, double y, double z,
                             double& cx, double& cy) {
	double ax,ay;
	GetCameraAngles(x, y, z, ax, ay);
	cx = (ax / AreaX + 1) / 2;
	cy = (ay / AreaY + 1) / 2;
}


