#include <iostream>
#include <fstream>

#include "bmp.h"

using namespace std;

#define BF_TYPE 0x4D42             /* "BM" */

#pragma pack(1)
struct BITMAPHEADER {
	unsigned short bfType;           /* The file type; must be BM. */
	unsigned int   bfSize;           /* The size, in bytes, of the bitmap file */
	unsigned short bfReserved1;      /* Reserved; must be zero. */
	unsigned short bfReserved2;      /* Reserved; must be zero. */
	unsigned int   bfOffBits;        /* The offset, in bytes, from the beginning of the BITMAPFILEHEADER */
    unsigned int   biSize;           /* The number of bytes required by the structure. */
    int            biWidth;          /* The width of the bitmap, in pixels. */
    int            biHeight;         /* The height of the bitmap, in pixels.
                                        If biHeight is positive, the bitmap is a bottom-up DIB and its origin is the
                                        lower-left corner.
                                        If biHeight is negative, the bitmap is a top-down DIB and its origin is the
                                        upper-left corner. */
    unsigned short biPlanes;         /* The number of planes for the target device. This value must be set to 1. */
    unsigned short biBitCount;       /* The number of bits per pixel */
    unsigned int   biCompression;    /* The type of compression for a compressed bottom-up bitmap */
    unsigned int   biSizeImage;      /* The size, in bytes, of the image. This may be set to zero for BI_RGB bitmaps. */
    int            biXPelsPerMeter;  /* The horizontal resolution, in pixels-per-meter, of the target device for the bitmap */
    int            biYPelsPerMeter;  /* The vertical resolution, in pixels-per-meter, of the target device for the bitmap. */
    unsigned int   biClrUsed;        /* The number of color indexes in the color table that are actually used by the bitmap.  */
    unsigned int   biClrImportant;   /* The number of color indexes that are required for displaying the bitmap. */
} __attribute__((packed));

/*
 * Constants for the biCompression field...
 */

#define BI_RGB       0             /* An uncompressed format. */
#define BI_RLE8      1             /* A run-length encoded (RLE) format for bitmaps with 8 bpp.
                                      The compression format is a 2-byte format consisting of a count
                                      byte followed by a byte containing a color index. */
#define BI_RLE4      2             /* An RLE format for bitmaps with 4 bpp.
                                      The compression format is a 2-byte format consisting of a count
                                      byte followed by two word-length color indexes */
#define BI_BITFIELDS 3             /* Specifies that the bitmap is not compressed and that the color
                                      table consists of three DWORD color masks that specify the red,
                                      green, and blue components, respectively, of each pixel.
                                      This is valid when used with 16- and 32-bpp bitmaps. */

#define BI_JPEG      4             /* Indicates that the image is a JPEG image */
#define BI_PNG       5             /* Indicates that the image is a PNG image. */

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

	    	unsigned short planes = ((BITMAPHEADER*)memblock)->biPlanes;
	    	unsigned short bits = ((BITMAPHEADER*)memblock)->biBitCount;
	    	unsigned int compression = ((BITMAPHEADER*)memblock)->biCompression;

	    	if ((planes == 1) && (bits == 24) && (compression == 0)) {
    	    	Width = ((BITMAPHEADER*)memblock)->biWidth;
    	    	int height = ((BITMAPHEADER*)memblock)->biHeight;
    	    	Height = height > 0 ? height : -height;
    	    	cout << "w=" << Width << " h=" << Height << std::endl;
    			Data = new TColor[Width * Height];
    	    	unsigned int start = ((BITMAPHEADER*)memblock)->bfOffBits;
    	    	unsigned int padSize = (4 - (Width * 3) % 4) % 4;
    	    	if (padSize > 0) {
    	    		unsigned int step = (Width + padSize) * sizeof(TColor);
    	    		for (unsigned int y = 0; y < Height; ++y) {
    	    			memcpy(Cell(0, y), memblock + start + y * step, Width * 3);
    	    		}
    	    	} else {
    	    		memcpy(Data, memblock + start, Width * Height * 3);
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

    unsigned int padSize  = (4 - (Width * 3) % 4) % 4;
    unsigned int sizeData = Width *  Height * 3 + Height * padSize;
    unsigned int sizeAll  = sizeData + sizeof(BITMAPHEADER);

    BITMAPHEADER header;
    header.bfType          = BF_TYPE;
    header.bfSize          = sizeAll;
    header.bfReserved1     = 0;
    header.bfReserved2     = 0;
    header.bfOffBits       = sizeof(BITMAPHEADER);
    header.biSize          = 40;
    header.biWidth         = Width;
    header.biHeight        = Height;
    header.biPlanes        = 1;
    header.biBitCount      = 24;
    header.biCompression   = 0;
    header.biSizeImage     = sizeData;
    header.biXPelsPerMeter = 0xB13; //(0x03C3 = 96 dpi, 0x0B13 = 72 dpi)
    header.biYPelsPerMeter = 0xB13;
    header.biClrUsed       = 0;
    header.biClrImportant  = 0;

    ofstream stream;
    stream.open (fileName, ios::out | ios::binary);
    stream.write((char*)&header, sizeof(BITMAPHEADER));

    if (padSize > 0) {
    	unsigned char pad[3] = {0,0,0};
    	for ( int y=0; y< Height; y++ ){
    		stream.write( (char*)Cell(0, y), 3 * Width );
    		stream.write( (char*)pad, padSize );
    	}
    } else {
    	stream.write((char*)Data, Width * Height * 3);
    }

    stream.close();
}
