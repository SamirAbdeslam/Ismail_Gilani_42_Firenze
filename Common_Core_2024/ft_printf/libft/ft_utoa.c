#include "libft.h"

static int	ft_count_nbr(unsigned long int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_utoa(unsigned long int n)
{
	char	*m;
	int		len;

	len = ft_count_nbr(n);
	m = ft_calloc (len + 1, sizeof(char));
	if (!m)
		return (NULL);
	while (n != 0)
	{
		m[--len] = n % 10 + '0';
		n = n / 10;
	}
	return (m);
}