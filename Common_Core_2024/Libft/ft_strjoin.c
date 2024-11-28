#include "libft.h"

char *ft_strjoin(char const *s1, char const *s2)
{
	char *ns;
	int i;
	i = 0;

	ns = malloc(ft_strlen(s1) + ft_strlen(s2));

	if(!ns)
		return(NULL);

	ns = (char *)s1;

	if(s2 == (void *) 0)
		return((char *)s1);

	while(s2[i] != '\0')
	{
		ns[ft_strlen(s1)] = s2[i];
		i++;
	}

	ns[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return(ns);
}
