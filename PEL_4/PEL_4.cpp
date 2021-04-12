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

void vypis(void *adresa, int delka, int format, char typ[])
{
    printf("Adresa: 0x%p   Delka: %dB  Hodnoty:\n", adresa, delka);

    if (strcmp(typ, "bin") == 0)
    {
        unsigned char* b = (unsigned char*)adresa;
        unsigned char byte;
        int i, j;

        for (i = delka - 1; i >= 0; i--) {
            for (j = 7; j >= 0; j--) {
                byte = (b[i] >> j) & 1;
                printf("%u", byte);
            }
            if (i % (format / 8) == 0) putchar(' ');
            if (i % 4 == 0) putchar('\n');
        }
        puts("");

    }
    else if (strcmp(typ, "hex") == 0)
    {
        for (size_t i = 0; i < (delka / (format / 8)); ++i)
        {
            if (format == 8)
            {
                unsigned char bit8 = *((unsigned char*)adresa + i);
                printf("%8x ", bit8);
            }
            else if (format == 16)
            {
                unsigned short int bit16 = *((unsigned short int*)adresa + i);
                printf("%8x ", bit16);
            }
            else if (format == 32)
            {
                unsigned int bit32 = *((unsigned int*)adresa + i);
                printf("%8x ", bit32);
            }
            else return;
            
            auto prvek = ((int*)adresa)[i];

            if (((i + 1) % (sizeof(prvek) / (format / 8))) == 0)
                printf("\n");
        }
        printf("\n");
    }
    else
    {
        for (int i = delka - 1; i >= 0; i--)
        {
            printf("%d ", (unsigned int*)adresa + i);
            if (i % 4 == 0) putchar('\n');
        }
    }
}
        
int main()
{
    srand(time(NULL));
    int i = rand_int();
    printf_s("Hodnota nahodne generovane promenne typu int: %d\n", i);
    putchar('\n');

    char typ[4];
    do
    {
        printf("Zadejte typ zobrazene hodnoty (bin/hex/dek): ");
        scanf_s("%3s", typ, 4);
    }     
    while (strcmp(typ, "bin") != 0 && strcmp(typ, "hex") != 0 && strcmp(typ, "dek") != 0);
    
    int format = 0;
    if (strcmp(typ, "dek") != 0)
    {
        while (format != 8 && format != 16 && format != 32)
        {
            printf("\nZadejte format vypisu hodnot (8/16/32): ");
            scanf_s("%d", &format);
            printf("\n");
        }
    }

    auto* adresa = &i;
    auto delka = sizeof(i);

    vypis(adresa, delka, format, typ);
    printf("\n");

    unsigned int pole[20];

    srand(time(NULL));
    for (int i = 0; i < 20; i++)
        pole[i] = rand_int();

    auto* adresa_pole = &pole;
    auto delka_pole = sizeof(pole);

    vypis(adresa_pole, delka_pole, format, typ);
}