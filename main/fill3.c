#include <stdio.h>
#include <stdlib.h>

//Скорость поиска от размера ключей

int main()
{
	FILE* open = fopen("instructions.txt", "w");

	fprintf(open, "MASS 100000 999999\n");
	for (int i = 100000; i < 1000000; i = i + 50000)
	{
		fprintf(open, "GET key%d\n", i);
	}

	/*
	fprintf(open, "MASS 1000000 9999999\n");
	for (int i = 1000000; i < 10000000; i = i + 500000)
	{
		fprintf(open, "GET key%d\n", i);
	}
*/
/*
	fprintf(open, "MASS 10000 99999\n");
	for (int i = 10000; i < 100000; i = i + 5000)
	{
		fprintf(open, "GET key%d\n", i);
	}
*/
	fclose(open);
}