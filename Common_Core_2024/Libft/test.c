#include <stdio.h>
#include <stdlib.h>
#include "ft_calloc.c"
void *ft_calloc(size_t nmemb, size_t size);

int main()
{
	int size = 10;
	
	printf("%p\n", calloc(size, 8));
	printf("%p", ft_calloc(size, 8));
}
