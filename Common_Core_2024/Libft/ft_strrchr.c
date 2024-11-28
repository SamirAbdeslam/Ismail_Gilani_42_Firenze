#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	t;
	int	i;

	i = ft_strlen(s);
	t = (unsigned char)c;	
	while (i)
	{
		if (s[i] == t)
		{
			return ((char *)&s[i]);
		}
		i--;
	}
	if (s[i] == t)
		return ((char *)&s[i]);
	return (NULL);
}
