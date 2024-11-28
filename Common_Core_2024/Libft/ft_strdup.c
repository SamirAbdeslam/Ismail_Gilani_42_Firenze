#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*mem;

	mem = ft_calloc(ft_strlen(s) + 1, 1);
	if (!mem)
		return (NULL);
	ft_strlcpy (mem, s, ft_strlen(s) + 1);
	return (mem);
}
