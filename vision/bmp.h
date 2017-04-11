#ifndef BMP_H_
#define BMP_H_

#include "utils.h"

typedef const unsigned char TColor[3];

class TRGBImage : public TImage<unsigned char> {
public:

	TRGBImage(int width, int height) :
		TImage(width, height, 3) {}

	TRGBImage(const char* bmpfile);

	void SaveBMP(const char* fileName);
};

#endif /* BMP_H_ */
