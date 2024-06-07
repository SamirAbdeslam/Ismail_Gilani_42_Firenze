/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:34:12 by igilani           #+#    #+#             */
/*   Updated: 2024/06/02 23:34:14 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

typedef struct s_list
{
	unsigned long int	num;
	char				*value;
}	t_list;

unsigned long int	ft_atoi(const char *str);
unsigned long int	gethundredz(unsigned long int num,
						unsigned long int *appnum, unsigned long int i);
unsigned long int	*getnumbers(unsigned long int num,
						unsigned long int *appnum);
unsigned long int	gethundreds(unsigned long int num);
unsigned long int	gettenz(unsigned long int num);
unsigned long int	gettens(unsigned long int num);
unsigned long int	getones(unsigned long int num);
char				*ft_getnb(unsigned long int fd);
char				*ft_getval(unsigned long int fd, char *c);
char				*ft_strdup(char *src);
t_list				*process(const char *file);
int					error(int num_error);

#endif
