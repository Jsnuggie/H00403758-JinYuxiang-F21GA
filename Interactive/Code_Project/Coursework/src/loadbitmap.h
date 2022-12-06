#ifndef BMP
#define BMP

#include "GL/glew.h"
#include <stdio.h>


#pragma pack(1)

#define WORD unsigned short
#define DWORD unsigned int
#define LONG int

typedef struct tagBITMAPFILEHEADER
{
	WORD  bfType;
	DWORD bfSize;
	WORD  bfReserved1;
	WORD  bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER, * PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER;



GLuint loadbitmap(const char* filename, unsigned char*& pixelBuffer, BITMAPINFOHEADER* infoHeader, BITMAPFILEHEADER* fileHeader);

#endif //BMP
#pragma once

