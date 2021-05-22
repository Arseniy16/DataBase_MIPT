#include <stdio.h>
#include <stdlib.h>

//Скорость поиска от количества ключей

int main()
{
	FILE* open = fopen("instructions.txt", "w");
	for (int i = 100000; i < 1000000; i = i + 10000)
	{
		fprintf(open, "MASS 0 %d\n", i);
		fprintf(open, "GET key%d\n", i);
	}
	fclose(open);
}