#ifndef BMP_H_
#define BMP_H_

#include "utils.h"

class TRGBImage : public TImage<TColor> {
public:

	TRGBImage(int width, int height) :
		TImage(width, height) {}

	TRGBImage(const char* bmpfile);

	void SaveBMP(const char* fileName);
};

#endif /* BMP_H_ */
