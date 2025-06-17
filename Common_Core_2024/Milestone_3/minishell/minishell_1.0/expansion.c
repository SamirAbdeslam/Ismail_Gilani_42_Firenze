/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:22:14 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/04 15:44:21 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	while_not_var(char *s, char *t, int *i, bool expand)
{
	while (t[*i] != '\0')
	{
		if (t[*i] == '$'
			&& (!is_space(t[*i + 1]) && t[*i + 1] != '\0' && t[*i + 1] != '"' && t[*i + 1] != '\'')
			&& (is_quoted(s, &t[*i]) != 1 || expand))
			break ;
		if (t[*i] == '$' && is_quoted(s, &t[*i]) == 0 && (t[*i + 1] == '"' || t[*i + 1] == '\''))
			break ;
		*i = *i + 1;
	}
}

char	*get_expanded_var(char *s, int *idx, t_data *data)
{
	int	i;
	char	*name;
	char	*r;

	if (s[0] == '\0')
		return (NULL);
	i = 1;
	while (s[i] != '\0' && s[i] != '$' && s[i] != '"' && s[i] != '\'' && !is_space(s[i]))
		i++;
	name  = ft_buffjoin(ft_strndup(&s[1], (i - 1)), "=");
	r = ft_strdup(check_env(data, name));
	free(name);
	*idx = *idx + i;
	return (r);
}

char	*expand_dollar(char *s, t_data *data, bool expand)
{
	int	i;
	char	*t;
	char	*r;

	i = 0;
	t = s;
	r = NULL;
	while (t[i] != '\0')
	{
		while_not_var(s, t, &i, expand);
		if (!r)
			r = ft_strndup(t, i);
		else
			r = ft_merge(r, ft_strndup(t, i));
		r = ft_merge(r, get_expanded_var(&t[i], &i, data));
		t += i;
		i = 0;
	}
	free(s);
	return (r);
}
