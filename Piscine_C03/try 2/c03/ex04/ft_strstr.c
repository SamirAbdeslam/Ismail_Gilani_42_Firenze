/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:46:13 by igilani           #+#    #+#             */
/*   Updated: 2024/05/27 12:46:14 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	if (*to_find == '\0' && *str)
	{
		return (str);
	}
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] != '\0' && str[i + j] == to_find[j])
		{
			j++;
		}
		if (to_find[j] == '\0')
		{
			return (&str[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int main()
{
    char src[] = "llo";
    char to_find[] = "Hello";
    char *result = ft_strstr(src, to_find);
    
    if (result != NULL)
    {
        printf("Trovata: %s\n", result);
    }
    else
    {
        printf("Non trovata\n");
    }
    return 0;
}*/
