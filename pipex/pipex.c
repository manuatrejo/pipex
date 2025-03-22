// gestión de el here_doc

char	*path_in_env(char *path, char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (path[j] == env[i][j])
			j++;
		if (j == 4)
			return (env[i] + 5);//porque es el siguiente a PATH=
	}
	return (NULL);
}

char	*execve_input(char *cmd1, char **env)
{
	int		i;
	char	*temp;
	char	*input;
	char	**paths;

	i = -1;
	paths = ft_split(path_in_env("PATH", env), ':');
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		input = ft_strjoin(temp, cmd1);
		free(temp);
		if (access(temp, X_OK | F_OK) == 0)
		{
			free_array(paths);
			return (input);
		}
		free(input);
	}
	free_array(paths);
}

void	exec(char *cmd, char **env)
{
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	if (execve(execve_input(cmds[0], env), cmds, env) == -1)
		free_array(cmds);
		
}

void	pipes(char **env, char *cmd)
{
	int	pipe_fds[2];
	pid_t	pid;


	pipe(pipe_fds);
	pid = fork();
	if (pid < 0)
		exit(0);
	if (pid != 0)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], 1);//redirige la salida al pipe de escritura
		exec(cmd, env);
	}
	else
	{
		close(pipe_fds[1]);
		dup2(pipe_fds[0], 0);// pasa la entrada al pipe de lectura
	}
}

int	main(int argc, char **argv, char **env)
{


	open_files
	dup2(fd_in, 0);
	
	
}
// heredoc, número de argumentos < 4, abrir archivos de entrada y salida, hacer pipe y fork
// y ejecutar las instrucciones 