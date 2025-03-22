/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:57:33 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 21:41:53 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char **count_words(char *str)
{
	int i = 0;
	int count = 0;

	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i])
			count++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			i++;
	}
	return((char**)malloc((count + 1) * sizeof(char*)));
}

char *ft_substr(char *str, int len)
{
	int i = 0;
	char *sub = (char*)malloc((len + 1) * sizeof(char));
	while(str[i] && i < len)
	{
		sub[i] = str[i];
		i++;
	}
	sub[i] = '\0';
	return(sub);
}

int main(int argc, char **argv)
{
	int i = 0;
	int j = 0;
	int a = 0;
	if (argc != 2)
	{
		write(1, "\n", 1);
		return(0);
	}
	char **m = count_words(argv[1]);
	if(!m)
		return(0);
	while (argv[1][i])
	{
		while (argv[1][i] && (argv[1][i] == ' ' || argv[1][i] == '\t'))
			i++;
		if (!argv[1][i])
			break;
		j = i;
		while (argv[1][i] && (argv[1][i] != ' ' && argv[1][i] != '\t'))
			i++;
	}
}