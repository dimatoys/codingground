/*
 * camera.h
 *
 *  Created on: Apr 5, 2017
 *      Author: p2711068
 */

#ifndef CAMERA_H_
#define CAMERA_H_

class TCamera {
	double X;
	double Y;
	double Z;

	double AX;
	double AY;
	double S;

	double AreaX;
	double AreaY;

public:

	TCamera(double x,
	        double y,
	        double z,
	        double ax,
	        double ay,
	        double s,
			double areax,
			double areay) {
		X = x;
		Y = y;
		Z = z;
		AX = ax;
		AY = ay;
		S = s;
		AreaX = areax;
		AreaY = areay;
	}

	void GetCameraPixel(double x, double y, double z, double& cx, double& cy);
	void GetCameraAngles(double x, double y, double z, double& ax, double& ay);
};



#endif /* CAMERA_H_ */
