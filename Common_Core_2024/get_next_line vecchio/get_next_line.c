/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:05:49 by igilani           #+#    #+#             */
/*   Updated: 2025/01/20 17:49:49 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **stash)
{
    char	*line;
    char	*new_pos;
    char	*tmp;
    int     i;

    if (!*stash)
        return (NULL);
    new_pos = ft_strchr(*stash, '\n');
    ft_printf("Stash2: |%s|\n", *stash);
    ft_printf("New_pos: |%s|\n", new_pos);
    if (new_pos)
    {
        //ft_printf("Len: %d, stash[4]: %c\n", (int)ft_strlen(*stash), *stash[1]);
        line = (char *)ft_calloc(ft_strlen(*stash) + 1, sizeof(char));
        i = 0;
        while (stash && *stash[i] != '\0' && *stash[i] != '\n')
        {
            line[i] = *stash[i];
            i++;
        }
        //ft_printf("I: %d, stash: %c\n", i, *stash[i]);
        line[i] = '\n';
        tmp = ft_strdup(new_pos + 1);
        free(*stash);
        *stash = tmp;
    }
    else
    {
        line = ft_strdup(*stash);
        free(*stash);
        *stash = NULL;
    }
    return (line);
}

static int	read_and_stash(int fd, char *stash)
{
    char	*buffer;
    ssize_t	bytes_read;
    char	*tmp;
    
    //ft_printf("Entro in funzione");
    if (!stash)
        stash = ft_calloc(1, sizeof(char));
    buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
    if (!buffer)
        return (-1); //attenzione
    bytes_read = 1;
    while(!ft_strchr(*stash, '\n') && bytes_read > 0)
    {
        //ft_printf("Entro read_stash, Stash: |%s|\n", *stash);
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0';
            if (*stash)
            {
                tmp = ft_strjoin(*stash, buffer); //probabile leak
                free(*stash);
                *stash = tmp;
            }
            else
            {
                *stash = ft_strdup(buffer);
            }
        }
    }
    //ft_printf("Stash2: |%s|\n", *stash);
    //ft_putstr_fd(2, 
    free(buffer);
    return (bytes_read);
}

char	*get_next_line(int fd)
{
    static char	*stash;
    int			bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    //stash = NULL; qua perdi via via informazioni ogni volta che la richiami;
    //inutile inizializzare poiche statica
    bytes_read = read_and_stash(fd, &stash);
    if (bytes_read < 0 || (bytes_read == 0 && (!stash)))
    {
        free(stash);
        stash = NULL;
        return (NULL);
    }
    if (stash && *stash == '\0')
    {
        free(stash);
        stash = NULL;
        return (ft_strdup(""));
    }
    return (extract_line(&stash));
}

int main()
{
    int fd;
    char *str;

    fd = open("nl", O_RDONLY);
    str = get_next_line(fd);
    ft_printf("%s", get_next_line(fd));
}
