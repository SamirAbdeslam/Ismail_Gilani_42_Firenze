/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:02:56 by igilani           #+#    #+#             */
/*   Updated: 2025/02/06 18:26:17 by igilani          ###   ########.fr       */
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
void	free_resources(char **arr, char **arr2, int exit_code);