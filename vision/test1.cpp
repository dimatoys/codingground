#include "bmp.h"

int main () {
	TRGBImage img(32, 32);

	TColor bg = {127, 255, 255};

	img.DrawRect(0, 0, img.Width, img.Height, bg);

	//dumpBin(img.Cell(0, 0), img.Width * img.Height * 3);

    img.SaveBMP("test1.bmp");
    return 0;
}
