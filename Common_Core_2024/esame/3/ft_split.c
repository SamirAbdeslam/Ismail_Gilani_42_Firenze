/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:24:15 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 18:47:29 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char  **count_words(char *str)
{
	int i = 0;
	int count = 0;

	while(str[i])
	{
		while(str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			count++;
		while(str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
	}
	return((char**)malloc((count + 1) * sizeof(char*)));
}

char *ft_substr(char *str, int len)
{
	int i = 0;
	char *sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return(NULL);
	while (str[i] && i < len)
	{
		sub[i] = str[i];
		i++;
	}
	sub[i] = '\0';
	return(sub);
}

char    **ft_split(char *str)
{
	int a = 0;
	int i = 0;
	int j = 0;
	
	if (!str)
		return(NULL);
	char **m = count_words(str);
	if (!m)
		return(NULL);
	while(str[i])
	{
		while(str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (!str[i])
			break;
		j = i;
		while(str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
		m[a] = ft_substr(&str[j], i - j);
		if(!m[a])
			return(NULL);
		a++;
	}
	m[a] = NULL;
	return(m);
}

int main()
{
	char *str = "Cacato nel puzzo con mio fratello Cinghiale mentre Domenico puzzo nel cagato";
	char **arr = ft_split(str);
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
	return (0);
}