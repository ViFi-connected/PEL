#include <stdio.h>
#include <stdint.h>
#include <iostream>

constexpr auto ASCII_SIZE = 256;

void decToBinary(unsigned int n)
{
	for (int i = 31; i >= 0; i--) {
		int k = n >> i;
		(k & 1) ? putchar('1') : putchar('0');
		if (i % 4 == 0)
			putchar('\t');
	}
	putchar('\n');
}

bool getParity(unsigned int n)
{
	bool parity = 0;
	while (n)
	{
		parity = !parity;
		n = n & (n - 1);
	}
	return parity;
}

char getMaxOccuringChar(char* str)
{
	int count[ASCII_SIZE] = { 0 };

	size_t len = strlen(str);
	int max = 0;
	char result{};

	if (str == NULL)
		return '\0';

	for (int i = 0; i < len; i++)
	{
		count[str[i]]++;
		if (max < count[str[i]])
		{
			max = count[str[i]];
			result = str[i];
		}
		else if (max == count[str[i]] && (str[i] < result))
			result = str[i];
	}
	return result;
}

int main()
{
	printf("TEST PRVNI FUKCE\n");

	unsigned int hodnota = 42069;

	printf("HODNOTA: %d\n", hodnota);

	printf("BINARNI VYPIS: \n");
	decToBinary(hodnota);

	printf("PARITA HODNOTY: ");
	puts((getParity(hodnota)) ? "LICHA\n" : "SUDA\n");

	printf("TEST DRUHE FUKCE\n");

	char textovy_retezec[] = "Hello World!";
	printf("RETEZEC: ");
	puts(textovy_retezec);

	char znak_cetnost = getMaxOccuringChar(textovy_retezec);
	printf("ZNAK S NEJVYSSI CETNOSTI JE: %c\n", znak_cetnost);
}