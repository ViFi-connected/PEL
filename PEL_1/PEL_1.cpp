#include <iostream>
using namespace std;

int main()
{
    uint16_t bez_znamenka, i;
    int16_t znamenko, j;
 
    bez_znamenka = i = numeric_limits<uint16_t>::max() - 20;
    znamenko = j = numeric_limits<int16_t>::max() - 20;

    do 
    {
        i++;
        j++;
        printf("%d %d, hex: %x %x\n", i, j, i, j);
    } while (i > bez_znamenka && j > znamenko);
}
