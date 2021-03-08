#include <iostream>
#include <stdlib.h>
#include <time.h>

int rand_int(void) {
    union {
        int i;
        unsigned char uc[sizeof(int)];
    } u;
    for (size_t i = 0; i < sizeof u.uc; i++) {
        u.uc[i] = rand();
    }
    return u.i;
}

void vypis(void* adresa, int delka, int format)
{
    printf("Adresa: 0x%p   Delka: %dB  Hodnoty:\n", adresa, delka);

    for (size_t i = 0; i < (delka / (format / 8)); ++i ) 
    { 
        switch ( format )
        {
            case 8:
            {
                unsigned char bit8 = *((unsigned char*)adresa + i);
                printf("%8x ", bit8);
                break;
            }
            case 16:
            {
                unsigned short int bit16 = *((unsigned short int*)adresa + i);
                printf("%8x ", bit16);
                break;
            }
            case 32:
            {
                unsigned int bit32 = *((unsigned int*)adresa + i);
                printf("%8x ", bit32);
                break;
            }
            default:
                printf("Zadejte spravny format!");
                return;
        }
        auto prvek = ((int*)adresa)[i];

        if (((i + 1) % (sizeof(prvek) / (format / 8))) == 0)
            printf("\n");
    }
    printf("\n");
}

int main()
{
    printf("Zadejte hodnotu promenne typu int: ");

    int i = 0;
    scanf_s("%d", &i);

    int format = 0;
    while (format != 8 && format != 16 && format != 32)
    {
        printf("Zadejte format vypisu hodnot (8/16/32): ");
        scanf_s("%d", &format);
        printf("\n");
    }

    auto* adresa = &i;
    auto delka = sizeof(i);

    vypis(adresa, delka, format);
    printf("\n");

    unsigned int pole[20];

    srand(time(NULL));
    for (int i = 0; i < 20; i++)
        pole[i] = rand_int();

    auto* adresa_pole = &pole;
    auto delka_pole = sizeof(pole);

    vypis(adresa_pole, delka_pole, format);
}