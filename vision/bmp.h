#ifndef BMP_H_
#define BMP_H_

void dumpBin(void* ptr, int size);

typedef const unsigned char TColor[3];

class TRGBImage {
	unsigned char* data;
public:
	int Width;
	int Height;
	int Depth;

	TRGBImage(int width, int height) {
		Width = width;
		Height = height;
		Depth = 3;
		data = new unsigned char[Width * Height * Depth];
	}

	unsigned char* Cell(int x, int y) {
		return data + (y * Width + x) * Depth;
	}

	void DrawPixel(int x, int y, TColor& color);
	void DrawRect(int startx, int starty, int width, int height, TColor& color);

	void SaveBMP(const char* fileName);

	~TRGBImage() {
		delete data;
	}
};

#endif /* BMP_H_ */
