#include <iostream>
#include <conio.h>

typedef struct Struct
{
    int degrees = 0;
    char cardinal = 0;
    float minutes = 0.0;
    float seconds = 0.0;
}Struct;

char ctiZnak()
{
    return _getch();
}

template <typename T>
T inputNonDecimal(int j)
{   
    int i, number;
    number = i = 0;
    char c = 0;
    while (i < j)
    {
        c = ctiZnak();

        if ((c >= '0') && (c <= '9'))
        {
            number *= 10;
            number += c - '0';
            printf("%d", c - '0');
            i++;
        }
        else if (c == '\r')
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
    bool decimal = false;
    char c = 0;

    number = 0.0;
    f = 1.0;
    while (i < j)
    {
        c = ctiZnak();
        i++;

        if ((c >= '0') && (c <= '9'))
        {
            if (f == 1)
            {
                number *= 10;
                number += c - '0';
            }
            else
            {
                number += (c - '0') * f;
                f /= 10;
            }
            printf("%d", c - '0');
        }
        if ((c == '.' || i == 2) && decimal == false)
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

double gpsConvert(Struct gps, char format)
{
    printf("\nZadejte GPS souradnice: ");
    // nacitani stupnu - max 3 cislice
    gps.degrees = inputNonDecimal<int>(3);
    
    //nacitani svetove strany
    int i = 0;
    char c = 0;
    while (i < 1)
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

    //prepinac formatu
    switch (format)
    {
    case '1':
        // nacitani minut - max 2 cislice
        gps.minutes = inputNonDecimal<float>(2);

        //nacitani vterin
        gps.seconds = inputDecimal<float>(9);
        break;
    case '2':
        // nacitani minut
        gps.minutes = inputDecimal<float>(9);
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

    while (true)
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