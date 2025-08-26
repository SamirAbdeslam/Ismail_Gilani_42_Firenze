/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:37:14 by igilani           #+#    #+#             */
/*   Updated: 2025/08/25 18:37:23 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argo.h"

int parse_map(json *dst, FILE *stream)
{
	dst->type = MAP;
	dst->map.data = NULL;
	dst->map.size = 0;
	if(!accept(stream, '{'))
		return (-1);
	if (peek(stream) == '}')
	{
		accept(stream, '}');
		return (1);
	}
	while(1)
	{
		dst->map.data = realloc(dst->map.data, sizeof(pair) * (dst->map.size + 1));
		if (!dst->map.data)
			return (-1);
		json key_json;
		if (parse_string(&key_json, stream) != 1)
		{
			free(dst->map.data);
			return (-1);
		}
		if (!expect(stream, ':'))
		{
			free(dst->map.data);
			return (-1);
		}
		json value_json;
		if (parse_value(&value_json, stream) != 1)
		{
			free(dst->map.data);
			return (-1);
		}
		dst->map.data[dst->map.size].key = key_json.string;
		dst->map.data[dst->map.size].value = value_json;
		dst->map.size++;
		if (accept(stream, ','))
			continue;
		if (expect(stream, '}'))
			break;
		return(-1);
	}
	return(1);
}

int parse_integer(json *dst, FILE *stream)
{
	int nbr;
	int nbr_len = 0;
	
	nbr_len = fscanf(stream, "%d", &nbr);
	if (nbr_len == 1)
	{
		dst->type = INTEGER;
		dst->integer = nbr;
		return(1);
	}
	else
	{
		unexpected(stream);
		return(-1);
	}
}

int parse_string(json *dst, FILE *stream)
{
	char *str;
	int c = 0;
	int str_len = 0;

	str = malloc(sizeof(char));
	if (!str)
		return(-1);
	str[0] = '\0';

	if (!accept(stream, '"'))
		return(-1);
	
	while (peek(stream) != '"' && peek(stream) != EOF)
	{
		str_len++;
		str = realloc(str, (str_len + 1) * sizeof(char));
		if (!str)
			return(-1);
		c = getc(stream);
		if (c == '\\')
		{
			c = getc(stream);
			if (c == '"' || c == '\\')
				str[str_len - 1] = c;
			else
			{
				unexpected(stream);
				free(str);
				return(-1);
			}
		}
		else
			str[str_len - 1] = c;
	}
	str[str_len] = '\0';
	if (!expect(stream, '"'))
	{
		free(str);
		return(-1);
	}
	dst->type = STRING;
	dst->string = str;
	return(1);
}

int parse_value(json *dst, FILE *stream)
{
	int c = peek(stream);
	if (c == '"')
		return (parse_string(dst, stream));
	else if (isdigit(c))
		return(parse_integer(dst, stream));
	else if (c == '{')
		return(parse_map(dst, stream));
	else
	{
		unexpected(stream);
		return(-1);
	}
}

int	argo(json *dst, FILE *stream)
{
	int ret = 0;
	ret = parse_value(dst, stream);
	return (ret);
}