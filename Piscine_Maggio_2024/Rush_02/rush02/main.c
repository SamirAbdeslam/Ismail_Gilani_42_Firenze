/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:35:07 by igilani           #+#    #+#             */
/*   Updated: 2024/06/02 23:35:08 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ft.h"

void	stampa(t_list *tab, unsigned long int *appnum,
		unsigned long int num, char *str)
{
	int	i;
	int	j;
	int	q;
	int	flag;

	flag = 0;
	i = 0;
	if (num == 0 && str[0]=='0')
	{
	}
	else if (num == 0 && str[0]!='0')
	{
		error(1);
	}
	while (i < 100)
	{
		j = 0;
		while (j < 32)
		{
			if (tab[j].num == appnum[i] && appnum[i] != 0)
			{
				q = 0;
				if(flag == 1)
					write(1," ",1);
				while(tab[j].value[q])
				{
					write(1,&tab[j].value[q],1);
					q++;
					flag = 1;
				}
			}
			j++;
		}
		i++;
	}
	write(1,"\n",1);
}

void	liberamemoria(t_list *tab, unsigned long int *appnum)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		free(tab[i].value);
		i++;
	}
	appnum[0]=1;
	free(tab);
	free(appnum);
}

int	main(int argc, char **argv)
{
	unsigned long int		*appnum;
	unsigned long int		num;
	t_list					*tab;

	if (argc < 2 ||argc>3)
	{
		error(1);
		return(0);
	}
	appnum = (unsigned long int *)malloc(sizeof(unsigned long int) * 100);
	if (appnum == NULL)
		return (1);
	if(argc==2)
	{
		tab = process("numbers.dict");
		num = ft_atoi(argv[1]);
		appnum = getnumbers(num, appnum);
		stampa(tab, appnum, num,argv[1]);
	}
	if (argc==3)
	{
		tab = process(argv[1]);
		num = ft_atoi(argv[2]);
		appnum = getnumbers(num, appnum);
		stampa(tab, appnum, num,argv[1]);
	}	
	liberamemoria(tab, appnum);
	return (0);
}
