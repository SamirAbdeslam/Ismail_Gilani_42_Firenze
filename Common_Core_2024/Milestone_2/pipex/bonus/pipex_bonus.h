/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:02:56 by igilani           #+#    #+#             */
/*   Updated: 2025/05/03 15:08:09 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "tha_supreme_lib/tha_supreme_lib.h"

char	**ft_split(char const *s, char c);
void	error_handle(int error, int exit_type);
void	ft_free(char **tab);
char	**get_path(char **env, int file);
char	*find_cmd_path(char *cmd, char **path_dirs);
void	exec(char **argv, char **env, char **path, int cmd_index);
void	heredoc(char **argv);
int		open_file(char *file, int flags);