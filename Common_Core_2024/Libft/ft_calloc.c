#include "libft.h"

void *ft_calloc(size_t nmemb, size_t size)
{
	const void *mem;
	mem = malloc(nmemb * size);
	
	if(!mem)
		return(NULL);

	ft_bzero((char *)mem, nmemb * size);

	return((char *)mem);
}
