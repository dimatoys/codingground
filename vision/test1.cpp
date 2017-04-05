#include "bmp.h"

int main () {
	TRGBImage img(32, 32);

	unsigned char bg[] = {0, 255, 255};

	for (int y= 0; y < img.Height; ++y) {
		for (int x = 0; x < img.Width; ++x) {
			img.DrawPixel(x, y, bg);
		}
	}

	//dumpBin(img.Cell(0, 0), img.Width * img.Height * 3);

    img.SaveBMP("test1.bmp");
    return 0;
}
