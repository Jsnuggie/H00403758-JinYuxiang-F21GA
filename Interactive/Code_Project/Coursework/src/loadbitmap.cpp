#include "loadbitmap.h"


GLuint loadbitmap(const char* filename, unsigned char*& pixelBuffer, BITMAPINFOHEADER* infoHeader, BITMAPFILEHEADER* fileHeader)
{
	FILE* bitmapFile;

#ifdef _MSC_VER
	errno_t err = fopen_s(&bitmapFile, filename, "rb");
	if (err != 0)
	{
		printf("loadbitmap - open failed for %s\n", filename);
		return NULL;
	}
#else
	bitmapFile = fopen(filename, "rb");
#endif

	if (bitmapFile == NULL)
	{
		printf("loadbitmap - open failed for %s\n", filename);
		return NULL;
	}

	fread(fileHeader, 14, 1, bitmapFile);

	if (fileHeader->bfType != 0x4D42)
	{
		printf("loadbitmap - type failed \n");

		return NULL;
	}

	fread(infoHeader, sizeof(BITMAPINFOHEADER), 1, bitmapFile);

	if (infoHeader->biBitCount < 24)
	{
		printf("loadbitmap - bitcount failed = %d\n", infoHeader->biBitCount);

		return NULL;
	}

	fseek(bitmapFile, fileHeader->bfOffBits, SEEK_SET);

	pixelBuffer = new unsigned char[infoHeader->biWidth * infoHeader->biHeight * (infoHeader->biBitCount / 8)];
	fread(pixelBuffer, sizeof(unsigned char), infoHeader->biWidth * infoHeader->biHeight * (infoHeader->biBitCount / 8), bitmapFile);

	fclose(bitmapFile);

	if (infoHeader->biBitCount == 32)
	{
		unsigned char c;
		for (int i = 0; i < infoHeader->biWidth * infoHeader->biHeight; i++)
		{
			c = pixelBuffer[i * 4];
			pixelBuffer[i * 4] = pixelBuffer[i * 4 + 3];
			pixelBuffer[i * 4 + 3] = c;
			c = pixelBuffer[i * 4 + 1];
			pixelBuffer[i * 4 + 1] = pixelBuffer[i * 4 + 2];
			pixelBuffer[i * 4 + 2] = c;
		}
	}

	printf("loadbitmap - loaded %s w=%d h=%d bits=%d\n", filename, infoHeader->biWidth, infoHeader->biHeight, infoHeader->biBitCount);
	return 0;
}