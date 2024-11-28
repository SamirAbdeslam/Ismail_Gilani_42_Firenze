/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:28:45 by igilani           #+#    #+#             */
/*   Updated: 2024/05/21 13:28:46 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	capitalize_character(char *c, int *capitalize_next)
{
	if (*c >= 'a' && *c <= 'z')
	{
		if (*capitalize_next)
		{
			*c -= 32;
			*capitalize_next = 0;
		}
	}
	else if (*c >= 'A' && *c <= 'Z')
	{
		if (!*capitalize_next)
			*c += 32;
		else
			*capitalize_next = 0;
	}
	else if (*c >= '0' && *c <= '9')
		*capitalize_next = 0;
	else
		*capitalize_next = 1;
}

char	*ft_strcapitalize(char *str)
{
	int	i;
	int	capitalize_next;

	i = 0;
	capitalize_next = 1;
	while (str[i] != '\0')
	{
		capitalize_character(&str[i], &capitalize_next);
		i++;
	}
	return (str);
}
