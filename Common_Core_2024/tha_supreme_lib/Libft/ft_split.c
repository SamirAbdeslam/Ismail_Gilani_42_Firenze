/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:56:43 by igilani           #+#    #+#             */
/*   Updated: 2025/06/23 19:34:03 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_count_words(char const *s, char c)
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

static void	*ft_free(char **t)
{
	int	i;

	i = 0;
	while (t[i])
		free(t[i++]);
	free(t);
	return (NULL);
}

static char	**ft_split_mechanic(char const *s, char **t, char c, int d)
{
	int	i;
	int	start;
	int	w;

	i = 0;
	start = 0;
	w = 0;
	while (s[i] && d--)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		t[w++] = ft_substr(s, start, (i - start));
		if (!t[w - 1])
			return (ft_free(t));
		if (s[i])
			i++;
	}
	t[w] = NULL;
	return (t);
}

char	**ft_split(char const *s, char c)
{
	char	**t;
	int		d;

	if (!s || s[0] == '\0')
		return (NULL);
	d = ft_count_words (s, c);
	t = (char **)malloc((d + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	t = ft_split_mechanic(s, t, c, d);
	return (t);
}
