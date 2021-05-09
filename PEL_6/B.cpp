#include "A.h"
#include "B.h"
#include <windows.h>
#include <iostream>

BMP read_bmp(const char *fileName)
{
    BMP bmp;
    FILE *f;
    BITMAPINFOHEADER ih, *ih_ptr;
    BITMAPFILEHEADER fh, *fh_ptr;
    ih_ptr = &ih;
    fh_ptr = &fh;

    // nacteni souboru
    fopen_s(&f, fileName, "rb");

    // file hlavicka
    if (f != NULL)
        fread(fh_ptr, sizeof(BITMAPFILEHEADER), 1, f);
    else
    {
        printf("Chyba pri nacitani souboru\n");
        exit(0);
    }
        
    // info hlavicka
    fread(ih_ptr, sizeof(BITMAPINFOHEADER), 1, f);

    bmp.width = ih.biWidth;
    bmp.height = ih.biHeight;
    bmp.colorDepth = ih.biBitCount;

    bmp.lineSize = ((bmp.width * bmp.colorDepth + 31) / 32) * 4;
    bmp.fileSize = bmp.lineSize * bmp.height;

    // alokovani pameti
    byte *data = (byte*)alloc_bytes(bmp.fileSize);

    // preskoceni hlavicky
    fseek(f, fh.bfOffBits, 0);

    // cteni dat
    fread(data, bmp.fileSize, 1, f);

    bmp.address = data;
    fclose(f);
    return bmp;
}

void show_bmp_data(unsigned char *address, long width, long height, unsigned int colorDepth)
{
    // vypis dat z hlavicek
    printf("Pocet bitu na pixel: %d\n", colorDepth);
    printf("Vyska obrazku: %d px\n", height);
    printf("Sirka obrazku: %d px\n\n", width);

    long lineSize = ((width * colorDepth + 31) / 32) * 4;

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            int pos = y * lineSize + x / 8;
            int bit = 1 << (7 - x % 8);
            if ((address[pos] & bit) > 0)
            {
                putchar(219);
            }
            else
                putchar(' ');
        }
        printf("\n");
    }
}