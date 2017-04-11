#include <iostream>
#include <fstream>

#include "bmp.h"

using namespace std;

#define TO_UINT(a, i) (((((((unsigned int)a[i+3] & 0xFF) << 8) + ((unsigned int)a[i+2] & 0xFF)) << 8) + ((unsigned int)a[i+1] & 0xFF)) << 8) + ((unsigned int)a[i] & 0xFF)
#define TO_USHORT(a, i) (((unsigned short)a[i+1] & 0xFF) << 8) + ((unsigned short)a[i] & 0xFF)

TRGBImage::TRGBImage(const char* bmpfile) {

	  Data = NULL;

	  ifstream file (bmpfile, ios::in|ios::binary|ios::ate);

	  if (file.is_open()) {
		streampos size = file.tellg();
	    file.seekg (0, ios::beg);

	    char* memblock = new char [size];
	    file.read (memblock, size);
	    file.close();

	    //dumpBin(memblock, 54);

	    if (memblock[0] == 'B' && memblock[1] == 'M') {

	    	unsigned short planes = TO_USHORT(memblock, 26);
	    	unsigned short bits = TO_USHORT(memblock, 28);
	    	unsigned int compression = TO_UINT(memblock, 30);

	    	if ((planes == 1) && (bits == 24) && (compression == 0)) {
    			Depth = 3;
    	    	Width = TO_UINT(memblock, 18);
    	    	Height = TO_UINT(memblock, 22);
    			Data = new unsigned char[Width * Height * Depth];
    	    	unsigned int start = TO_UINT(memblock, 10);
    	    	unsigned int step = (Width + (4 - (Width * 3) % 4) % 4) * Depth;
    	    	cout << " start=" << start << " w=" << Width << " h=" << Height << std::endl;
    	    	for (unsigned int y = 0; y < Height; ++y) {
	    			memcpy(Cell(0, y), memblock + start + y * step, Width * Depth);
	    		}
	    	} else {
		    	cout << " Not supported: planes=" << planes << " bits=" << bits << " compression=" << compression << std::endl;
	    	}
	    } else {
	    	cout << "File is not BMP:" << (char)memblock[0] << (char)memblock[1] << std::endl;
	    }

	    delete[] memblock;
	  } else {
		  cout << "Cannot open " << bmpfile << std::endl;
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
