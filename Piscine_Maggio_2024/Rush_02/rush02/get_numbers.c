/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:34:46 by igilani           #+#    #+#             */
/*   Updated: 2024/06/02 23:34:47 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ft.h"

unsigned long int	gethundredz(unsigned long int num,
	unsigned long int *appnum, unsigned long int i)
{
	unsigned long int	temp;
	unsigned long int	sottrai;

	sottrai = 0;
	appnum[i] = gethundreds(num);
	sottrai += appnum[i];
	i++;
	if (appnum[i - 1] != 0)
	{
		appnum[i - 1] = 100;
		appnum[i] = num / 100;
		temp = appnum[i - 1];
		appnum[i - 1] = appnum[i];
		appnum[i] = temp;
		i++;
	}
	appnum[i] = gettens(num - sottrai);
	sottrai += appnum[i];
	i++;
	appnum[i] = getones(num - sottrai);
	i++;
	return (i);
}

unsigned long int	getbillionz(unsigned long int num,
	unsigned long int *appnum)
{
	unsigned long int	i;

	i = 0;
	if (num >= 1000000000000000000)
	{
		i = gethundredz(num / 1000000000000000000, appnum, i);
		if (i >= 3 && appnum[i - 1] + appnum[i - 2] + appnum[i - 3] != 0)
			appnum[i++] = 1000000000;
	}
	if (num >= 1000000000000000)
	{
		i = gethundredz((num % 1000000000000000000) / 1000000000000000,
				appnum, i);
		if (i >= 3 && appnum[i - 1] + appnum[i - 2] + appnum[i - 3] != 0)
			appnum[i++] = 1000000;
	}
	if (num >= 1000000000000)
	{
		i = gethundredz((num % 1000000000000000) / 1000000000000, appnum, i);
		if (appnum[i - 1] + appnum[i - 2] + appnum[i - 3] != 0)
			appnum[i++] = 1000;
	}
	return (i);
}

unsigned long int	*getnumbers(unsigned long int num,
	unsigned long int *appnum)
{
	unsigned long int	i;

	i = getbillionz(num, appnum);
	if (num >= 1000000000)
	{
		i = gethundredz((num % 1000000000000) / 1000000000, appnum, i);
		appnum[i++] = 1000000000;
	}
	if (num >= 1000000)
	{
		i = gethundredz((num % 1000000000) / 1000000, appnum, i);
		if (i >= 3 && appnum[i - 1] + appnum[i - 2] + appnum[i - 3] != 0)
			appnum[i++] = 1000000;
	}
	if (num >= 1000)
	{
		i = gethundredz((num % 1000000) / 1000, appnum, i);
		if (i >= 3 && appnum[i - 1] + appnum[i - 2] + appnum[i - 3] != 0)
			appnum[i++] = 1000;
	}
	i = gethundredz(num % 1000, appnum, i);
	appnum[i] = -1;
	return (appnum);
}
