#pragma once

typedef struct BMP
{
    unsigned char *address;
    long width;
    long height;
    long lineSize;
    long fileSize;
    unsigned short colorDepth;
};

BMP read_bmp(const char *fileName);
void show_bmp_data(unsigned char *address, long width, long height, unsigned int colorDepth);


