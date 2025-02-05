#include "pipex.h"

void	free_split(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_resources(char **arr, char *path, int exit_code)
{
	free_split(arr);
	free_split(&path);
	exit(exit_code);
}

static char	*find_cmd_path(char *cmd, char **path_dirs)
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

static char	**get_path(char **env)
{
	char	*path_str;

	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (!*env)
	{
		error_handle(7, 1);
		return (NULL);
	}
	path_str = *env + 5;
	return (ft_split(path_str, ':'));
}

static void	child(int *fd, char **argv, char **env)
{
	int		file_in;
	char	*cmd_path1;
	char	**path;
	char	**cmd1;

	file_in = open(argv[1], O_RDONLY);
	if (file_in == -1)
		error_handle(5, 1);
	path = get_path(env);
	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		free_resources(path, NULL, 1); // Libera path se cmd1 fallisce
	cmd_path1 = find_cmd_path(cmd1[0], path);
	free_split(path); // Libera path subito dopo l'uso
	if (!cmd_path1)
		free_resources(cmd1, NULL, 127);
	dup2(file_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (execve(cmd_path1, cmd1, env) == -1)
	{
		if (cmd_path1 != cmd1[0])
			free(cmd_path1);
		free_resources(cmd1, NULL, 1);
	}
	close(file_in);
}

static void	parent(int *fd, char **argv, char **env)
{
	int		file_out;
	char	*cmd_path2;
	char	**path;
	char	**cmd2;

	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
		error_handle(6, 1);
	path = get_path(env);
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd2)
		free_resources(path, NULL, 1); // Libera path se cmd2 fallisce
	cmd_path2 = find_cmd_path(cmd2[0], path);
	free_split(path); // Libera path subito dopo l'uso
	if (!cmd_path2)
		free_resources(cmd2, NULL, 127);
	dup2(fd[0], STDIN_FILENO);
	dup2(file_out, STDOUT_FILENO);
	close(fd[1]);
	if (execve(cmd_path2, cmd2, env) == -1)
	{
		if (cmd_path2 != cmd2[0])
			free(cmd_path2);
		free_resources(cmd2, NULL, 1);
	}
	close(file_out);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		error_handle(0, 1);
	if (pipe(fd) == -1)
		error_handle(1, 1);
	pid1 = fork();
	if (pid1 == 0)
		child(fd, argv, env);
	pid2 = fork();
	if (pid2 == 0)
		parent(fd, argv, env);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}