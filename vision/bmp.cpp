#include <iostream>
#include <fstream>

#include "string.h"
#include "bmp.h"

using namespace std;

void dumpBin(void* ptr, int size) {
    for (int i = 0; i < size; ++i) {
    	if (i % 16 == 0) {
    		printf("\n%04X ", i);
    	}
    	printf(" %02X", (unsigned int)*(((unsigned char*)ptr) + i));
    }
}

void TRGBImage::DrawPixel(int x, int y, void* color) {
	memcpy(Cell(x, y), color, Depth);
}

void TRGBImage::DrawRect(int startx, int starty, int width, int height, void* color) {
	int endx = startx + width;
	int endy = starty + height;
	for (int y = starty; y < endy; ++y) {
		for (int x = startx; x < endx; ++x) {
			DrawPixel(x, y, color);
		}
	}
}


void TRGBImage::SaveBMP(const char* fileName) {
    unsigned char file[14] = {
        'B','M', // magic
        0,0,0,0, // size in bytes
        0,0, // app data
        0,0, // app data
        40+14,0,0,0 // start of data offset
    };

    unsigned char info[40] = {
        40,0,0,0, // info hd size
        0,0,0,0, // width
        0,0,0,0, // heigth
        1,0, // number color planes
        24,0, // bits per pixel
        0,0,0,0, // compression is none
        0,0,0,0, // image bits size
        0x13,0x0B,0,0, // horz resoluition in pixel / m
        0x13,0x0B,0,0, // vert resolutions (0x03C3 = 96 dpi, 0x0B13 = 72 dpi)
        0,0,0,0, // #colors in pallete
        0,0,0,0, // #important colors
    };

    int padSize  = (4 - (Width * 3) % 4) % 4;
    int sizeData = Width *  Height * 3 + Height * padSize;
    int sizeAll  = sizeData + sizeof(file) + sizeof(info);

    file[ 2] = (unsigned char)(sizeAll);
    file[ 3] = (unsigned char)(sizeAll >> 8);
    file[ 4] = (unsigned char)(sizeAll >> 16);
    file[ 5] = (unsigned char)(sizeAll >> 24);

    info[ 4] = (unsigned char)(Width);
    info[ 5] = (unsigned char)(Width >> 8);
    info[ 6] = (unsigned char)(Width >> 16);
    info[ 7] = (unsigned char)(Width >> 24);

    info[ 8] = (unsigned char)(Height);
    info[ 9] = (unsigned char)(Height >> 8);
    info[10] = (unsigned char)(Height >> 16);
    info[11] = (unsigned char)(Height >> 24);

    info[20] = (unsigned char)(sizeData);
    info[21] = (unsigned char)(sizeData >> 8);
    info[22] = (unsigned char)(sizeData >> 16);
    info[23] = (unsigned char)(sizeData >> 24);

    ofstream stream;
    stream.open (fileName, ios::out | ios::binary);

    stream.write( (char*)file, sizeof(file) );


    stream.write( (char*)info, sizeof(info) );

    unsigned char pad[3] = {0,0,0};

    for ( int y=0; y< Height; y++ )
    {
        stream.write( (char*)Cell(0, y), Depth * Width );
        stream.write( (char*)pad, padSize );
    }

    stream.close();
}
