/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:35:18 by igilani           #+#    #+#             */
/*   Updated: 2024/06/02 23:35:20 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ft.h"

unsigned long int	gethundreds(unsigned long int num)
{
	if (num >= 900)
		return (900);
	if (num >= 800)
		return (800);
	if (num >= 700)
		return (700);
	if (num >= 600)
		return (600);
	if (num >= 500)
		return (500);
	if (num >= 400)
		return (400);
	if (num >= 300)
		return (300);
	if (num >= 200)
		return (200);
	if (num >= 100)
		return (100);
	return (0);
}

unsigned long int	gettenz(unsigned long int num)
{
	if (num >= 19)
		return (19);
	if (num >= 18)
		return (18);
	if (num >= 17)
		return (17);
	if (num >= 16)
		return (16);
	if (num >= 15)
		return (15);
	if (num >= 14)
		return (14);
	if (num >= 13)
		return (13);
	if (num >= 12)
		return (12);
	if (num >= 11)
		return (11);
	return (10);
}

unsigned long int	gettens(unsigned long int num)
{
	if (num >= 90)
		return (90);
	if (num >= 80)
		return (80);
	if (num >= 70)
		return (70);
	if (num >= 60)
		return (60);
	if (num >= 50)
		return (50);
	if (num >= 40)
		return (40);
	if (num >= 30)
		return (30);
	if (num >= 20)
		return (20);
	if (num >= 10)
	{
		num = gettenz(num);
		return (num);
	}
	return (0);
}

unsigned long int	getones(unsigned long int num)
{
	if (num == 9)
		return (9);
	if (num == 8)
		return (8);
	if (num == 7)
		return (7);
	if (num == 6)
		return (6);
	if (num == 5)
		return (5);
	if (num == 4)
		return (4);
	if (num == 3)
		return (3);
	if (num == 2)
		return (2);
	if (num == 1)
		return (1);
	return (0);
}
