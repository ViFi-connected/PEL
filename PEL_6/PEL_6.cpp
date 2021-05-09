#include <iostream>
#include "A.h"
#include "B.h"

int main()
{
    BMP bmp = read_bmp("intelww4.bmp");
    dump(bmp.address, bmp.fileSize);
    show_bmp_data(bmp.address, bmp.width, bmp.height, bmp.colorDepth);
    dealloc(bmp.address);
}
