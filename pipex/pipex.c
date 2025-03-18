// gestión de el here_doc
here_doc

void	pipes(char **env, char *cmd)
{
	int	pipe_fds[2];
	pid_t	pid;


	pipe(pipe_fds);
	pid = fork();
	if (pid < 0)
		exit;
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