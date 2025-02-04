/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:58:50 by igilani           #+#    #+#             */
/*   Updated: 2025/02/04 19:29:29 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_cmd_path(char *cmd, char **path_dirs)
{
    int i = 0;
    char *full_path;
    int len;

    if (ft_strchr(cmd, '/') != NULL)
    {
        if (access(cmd, F_OK | X_OK) == 0)
            return (cmd);
        return (NULL);
    }
    while (path_dirs[i])
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
        i++;
    }
    return (NULL);
}

char **get_path(char **envp)
{
	char *path_str;

	while(*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if(!*envp)
		return(NULL);
	path_str = *envp + 5;
	return(ft_split(path_str, ':'));
}

int main(int argc, char **argv, char **envp)
{
	int	file_in;
	int	file_out;
	int	fd[2];
	int	id_pipe;
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd1;
	char	**cmd2;
	char	*cmd_path1;
	char	*cmd_path2;
	char	**path;
	int		errore;
	errore = 0;

	if (argc < 5)
	{
		errno = EINVAL;
		perror("Pochi argomenti");
		exit(EXIT_FAILURE);
	}

	file_in = open(argv[1], O_RDONLY);
	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if(file_in == -1 || file_out == -1)
	{
		perror("Errore apertura file");
		exit(EXIT_FAILURE);
	}

	id_pipe = pipe(fd);

	if(id_pipe == -1)
	{
		perror("Erorre pipe");
		exit(EXIT_FAILURE);
	}
	
	pid1 = fork();

	if(pid1 == -1)
	{
		perror("Errore fork");
		exit(EXIT_FAILURE);
	}
	
	path = get_path(envp);

	if(!pid1)
	{
		dup2(file_in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(file_in);
    	cmd1 = ft_split(argv[2], ' ');
		cmd_path1 = find_cmd_path(cmd1[0], path);
		if (!cmd_path1) {
  			perror("command not found");
  			exit(EXIT_FAILURE);
		}
		errore = execve(cmd_path1, cmd1, envp);
		if (errore == -1) {
			errore = 0;
			perror("errore execve");
  			exit(EXIT_FAILURE);
		}
	}

	pid2 = fork();

	if(pid2 == -1)
	{
		exit(EXIT_FAILURE);
	}

	if(!pid2)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(file_out, STDOUT_FILENO);
		close(fd[1]);
		cmd2 = ft_split(argv[3], ' ');
		cmd_path2 = find_cmd_path(cmd2[0], path);
		if (!cmd_path2) {
  			ft_putstr_fd("command not found", 2);
  			exit(EXIT_FAILURE);
		}
		errore = execve(cmd_path2, cmd2, envp);
		if (errore == -1) {
  			errore = 0;
			perror("errore execve");
			exit(EXIT_FAILURE);
		}
	}

close(fd[0]);
close(fd[1]);
close(file_in);
close(file_out);

waitpid(pid1, NULL, 0);
waitpid(pid2, NULL, 0);

exit(EXIT_SUCCESS);
return(0);
}
