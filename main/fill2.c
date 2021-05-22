#include <stdio.h>
#include <stdlib.h>

//Скорость вставки от количества ключей

int main()
{
	FILE* open = fopen("instructions.txt", "w");
	fprintf(open, "MASS 0 9999\n");
	for (int i = 10000; i < 1000000; i = i + 10000)
	{
		fprintf(open, "SET %d 1\n", i);
		fprintf(open, "MASS %d %d\n", i, i + 9999);
	}
	fprintf(open, "SET 1000000 1\n");
	fclose(open);
}