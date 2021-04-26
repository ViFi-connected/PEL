#include <iostream>
#include <windows.h>

unsigned char* read_bmp(const char* fname, BITMAPINFOHEADER* ih, BITMAPFILEHEADER* fh, int* _w, int* _h)
{
    
    FILE* f;
    
    // nacteni souboru
    fopen_s(&f, fname, "rb");

    // file hlavicka
    fread(fh, sizeof(BITMAPFILEHEADER), 1, f);

    // info hlavicka
    fread(ih, sizeof(BITMAPINFOHEADER), 1, f);

    int w = ih->biWidth;
    int h = ih->biHeight;

    int lineSize = (w / 8 + (w / 8) % 4);
    int fileSize = lineSize * h;

    // alokovani pameti
    unsigned char* img = (byte*)malloc(w * h), * data = (byte*)malloc(fileSize);

    // preskoceni hlavicky
    fseek(f, fh->bfOffBits, 0);

    // cteni dat
    fread(data, fileSize, 1, f);

    // dekodovani bitu
    int i, j, k, rev_j;
    for (j = 0, rev_j = h - 1; j < h; j++, rev_j--) {
        for (i = 0; i < w / 8; i++) {
            int fpos = j * lineSize + i, pos = rev_j * w + i * 8;
            for (k = 0; k < 8; k++)
                img[pos + (7 - k)] = (data[fpos] >> k) & 1;
        }
    }

    free(data);
    *_w = w; *_h = h;
    return img;
}

int main()
{
    BITMAPINFOHEADER ih;
    BITMAPFILEHEADER fh;

    int w, h, i, j;
    unsigned char* img = read_bmp("intelww4.bmp",&ih,&fh, &w, &h);

    // vypis dat z hlavicek
    printf("Velikost souboru: %d B\n", fh.bfSize);
    printf("velikost informacni hlavicky: %d B\n", ih.biSize);
    printf("Pocet bitu na pixel: %d\n", ih.biBitCount);
    printf("Vyska obrazku: %d px\n", ih.biHeight);
    printf("Sirka obrazku: %d px\n\n", ih.biWidth);

    // vykresleni bitmapy
    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++)
            printf("%c ", img[j * w + i] ? 219 : ' ');

        printf("\n");
    }
}
