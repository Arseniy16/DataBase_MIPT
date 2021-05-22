#include <stdio.h>
#include <stdlib.h>

//Скорость вставки от размера ключей

int main()
{
	FILE* open = fopen("instructions.txt", "w");

	for (int i = 100000; i < 1000000; i = i + 100000)
	{
		fprintf(open, "MASS %d %d\n", i, i+99998);
	}
	for (int i = 199999; i < 1000000; i = i + 100000)
	{
		fprintf(open, "SET %d 1\n", i);
	}

	/*
	for (int i = 1000000; i < 10000000; i = i + 1000000)
	{
		fprintf(open, "MASS %d %d\n", i, i+999998);
	}
	for (int i = 1999999; i < 10000000; i = i + 1000000)
	{
		fprintf(open, "SET %d 1\n", i);
	}
	*/
	fclose(open);
}