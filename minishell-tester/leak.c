#include <stdio.h>
#include <stdlib.h>

void leaker()
{
	char *A = (char *)malloc(sizeof(char));
	// free(A);
}

int main()
{
	leaker();
}