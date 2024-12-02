/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:56:43 by igilani           #+#    #+#             */
/*   Updated: 2024/12/02 18:27:02 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c, int f)
{
	int	d;
	int	p;
	int	i;

	d = 0;
	p = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && !p)
		{
			p = 1;
			d++;
		}
		else if (s[i] == c)
		{
			p = 0;
		}
		i++;
	}
	return (d);
}

static void	ft_free(char **t)
{
	int	w;
	
	if (!t[w - 1])
	{
		while (w-- > 0)
			free (t[w]);
		free (t);
		return (NULL);
	}
	return(NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**t;
	int		i;
	int		d;
	int		w;
	int		start;

	i = 0;
	w = 0;
	if (!s)
		return (NULL);
	d = ft_count_words (s, c);
	t = malloc((d + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	while (s[i] && d--)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		t[w++] = ft_substr(s, start, (i - start));
		if (!t[w - 1])
		{
			while (w-- > 0)
				free (t[w]);
			free (t);
			return (NULL);
		}
		i++;
	}
	t[w] = NULL;
	return (t);
}
