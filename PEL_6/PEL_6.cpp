#include <iostream>
#include "A.h"
#include "B.h"

int main()
{
    BMP bmp = read_bmp("trollface.bmp");
    show_bmp_data(bmp.address, bmp.width, bmp.height, bmp.colorDepth);
    dealloc(bmp.address);
}
