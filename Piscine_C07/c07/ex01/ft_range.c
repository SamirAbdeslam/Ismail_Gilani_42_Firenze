/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:10:01 by igilani           #+#    #+#             */
/*   Updated: 2024/05/30 12:10:02 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	*ft_range(int min, int max)
{
	if(min >= max)
		return(NULL);
		
	int	*arr;
	int	i;
	int	size;
	
	size = max - min;
	i = 0;

	arr = (int *) malloc(size * sizeof(int));
	
	if(arr == (NULL))
		return(NULL);
	
	while(i < size)
	{
		arr[i] = min + i;
		i++;
	}
		
	return(arr);
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Uso: %s <min> <max>\n", argv[0]);
        return 1;
    }

    int min = atoi(argv[1]);
    int max = atoi(argv[2]);
    int *result = ft_range(min, max);

    if (result == NULL) {
        printf("Errore: range non valido o allocazione di memoria fallita\n");
        return 1;
    }

    for (int i = 0; i < max - min; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);

    return 0;
}
