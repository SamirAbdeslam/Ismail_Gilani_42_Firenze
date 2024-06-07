/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:23:44 by igilani           #+#    #+#             */
/*   Updated: 2024/06/05 15:23:45 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	if(min >= max)
	{
		*range = NULL;
		return(0);
	}

	int	i;
	int	size;
	
	size = max - min;
	i = 0;

	*range = (int *) malloc(size * sizeof(int));
	
	if(*range == (NULL))
		return(-1);
	
	while(i < size)
	{
		(*range)[i] = min + i;
		i++;
	}
		
	return(size);
}
/*
int main()
{
    int	*range;
    int result = ft_ultimate_range(&range, 10, 20);

    printf("%d ", result);
    printf("\n");

    return 0;
}*/

/*Passare una matrice come input e poi far scorrere ogni stringa nella matrice fino al carattere nullo e utilizzare strcat per inserire il carattere separatore 
Size e' la grandezza effettiva dell'array */
