#include "libft.h"

char *ft_strrchr(const char *s, int c)
{
	int i;
	unsigned char t;

	i = ft_strlen(s);
	t = (unsigned char)c;
	
	while(i)
	{
		if(s[i] == t)
		{
			return((char *)&s[i]);
		}
		i--;
	}
	if(s[i] == t)
		return((char *)&s[i]);
	return(NULL);
}
