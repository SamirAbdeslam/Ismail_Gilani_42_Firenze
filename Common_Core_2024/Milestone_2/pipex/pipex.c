/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:52:31 by igilani           #+#    #+#             */
/*   Updated: 2025/03/07 18:59:52 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_cmd_path(char *cmd, char **path_dirs)
{
	int		i;
	int		len;
	char	*full_path;

	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	i = -1;
	while (path_dirs[++i])
	{
		len = ft_strlen(path_dirs[i]) + ft_strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
			return (NULL);
		ft_strlcpy(full_path, path_dirs[i], len);
		ft_strlcat(full_path, "/", len);
		ft_strlcat(full_path, cmd, len);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

char	**get_path(char **env, int file)
{
	char	*path_str;

	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (!*env)
	{
		close(file);
		error_handle(7, 1);
		return (NULL);
	}
	path_str = *env + 5;
	return (ft_split(path_str, ':'));
}

void	child(int *fd, char **argv, char **env)
{
	int		file_in;
	char	**path;

	close(fd[0]);
	file_in = open(argv[1], O_RDONLY, 0777);
	if (file_in == -1)
	{
		close(fd[1]);
		error_handle(5, 1);
	}
	path = get_path(env, file_in);
	if (dup2(file_in, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(0);
		close(1);
		close(fd[1]);
		close(file_in);
		error_handle(8, 1);
	}
	close(file_in);
	close(fd[1]);
	exec(argv, env, path, 2);
	ft_free(path);
}

void	parent(int *fd, char **argv, char **env)
{
	int		file_out;
	char	**path;

	close(fd[1]);
	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
	{
		close(fd[0]);
		error_handle(5, 1);
	}
	path = get_path(env, file_out);
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(file_out, STDOUT_FILENO) == -1)
	{
		close(0);
		close(1);
		close(fd[0]);
		close(file_out);
		error_handle(8, 1);
	}
	close(fd[0]);
	close(file_out);
	exec(argv, env, path, 3);
	ft_free(path);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (argc != 5)
		error_handle(0, 1);
	if (pipe(fd) == -1)
		error_handle(1, 1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error_handle(2, 0);
	}
	if (!pid)
		child(fd, argv, env);
	waitpid(pid, &status, 0);
	parent(fd, argv, env);
	return (0);
}
