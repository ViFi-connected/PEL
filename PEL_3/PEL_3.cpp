#include <iostream>
#include <conio.h>

typedef struct Struct
{
    int degrees = 0;
    char cardinal = 0;
    float minutes = 0.0;
    float seconds = 0.0;
};

char ctiZnak()                                  // nacitani znaku
{
    return _getch();
}

template <typename T>                        
T inputNonDecimal(int j)                        // funkce pro naètení celých èísel
{   
    int i, number;
    number = i = 0;
    char c = 0;
    while (i < j)                               // j je max poèet èíslic
    {
        c = ctiZnak();

        if ((c >= '0') && (c <= '9'))           // akceptuji jen cislice
        {
            number *= 10;                       // posouvani cislic v cisle
            number += c - '0';
            printf("%d", c - '0');              
            i++;
        }
        else if (c == '\r')                     // enter zrusi cyklus - dalsi cislo
            break;
    }
    printf(" ");
    return number;
}

template <typename T>
T inputDecimal(int j)
{
    int i = 0;
    float f, number;
    bool decimal = false;                       // flag jestli uz pocitam desetiny
    char c = 0;

    number = 0.0;
    f = 1.0;
    while (i < j)
    {
        c = ctiZnak();
        i++;

        if ((c >= '0') && (c <= '9'))
        {
            if (f == 1)                         // cely cislo
            {
                number *= 10;
                number += c - '0';
            }
            else
            {   
                number += (c - '0') * f;        // desetiny
                f /= 10;
            }
            printf("%d", c - '0');
        }
        if ((c == '.' || i == 2) && decimal == false)       // pokud zadam tecku nebo uz jsem zadal 2 cislice zacinam zadavat desetinny mista
        {
            f = 0.1F;
            printf(".");
            decimal = true;
        }
        else if (c == '\r')
            break;
    }
    return number;
}

double gpsConvert(Struct gps, char format)          // volani nacitacich funkci a vypocet
{
    printf("\nZadejte GPS souradnice: ");
    gps.degrees = inputNonDecimal<int>(3);          // nacitani stupnu - max 3 cislice
    
    int i = 0;
    char c = 0;
    while (i < 1)                                   // nacitani svetove strany
    {
        c = ctiZnak();

        if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        {
            gps.cardinal = c;
            printf("%c", c);
            i++;
        }
        else if (c == '\r')
            break;
    }
    printf(" ");
    
    switch (format)                                 // prepinac formatu
    {
    case '1':
        gps.minutes = inputNonDecimal<float>(2);    // nacitani minut - max 2 cislice
        gps.seconds = inputDecimal<float>(9);       // nacitani vterin - max 9 znaku
        break;
    case '2':
        gps.minutes = inputDecimal<float>(9);       // nacitani minut - max 9 znaku
        break;
    default:
        break;
    }
    return (gps.degrees + gps.minutes / 60.0 + gps.seconds / 3600.0);
}

int main()
{
    Struct gps;
    char c;

    printf("1) ddd N/S/E/W mm ss.ffffff\n");
    printf("2) ddd N/S/E/W mm.ffffff\n ");
    printf("\nZadejte format GPS souradnic: ");

    while (true)                // volba formatu
    {
        c = ctiZnak();

        if ((c == '1') || (c == '2'))
        {
            printf("%d", c - '0');
            break;
        }
    }
    printf("\n\nVysledek: %f", gpsConvert(gps, c));
    printf("\n");
}