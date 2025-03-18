// /*de momento lo que se necesita obtener es para la función
// execve es el path, el comando en formato legible para execve
// el path se puede obtener usando char *path = getenv("PATH")
// */

// # include <unistd.h>
// # include <stdio.h>
// # include <sys/types.h>
// # include <sys/wait.h>
// # include<sys/types.h>
// # include<sys/stat.h>
// # include <fcntl.h>  
// # include <stdlib.h>
// int main(int argc, char **argv, char **env)
// {
	
// }
// execve
// /*
// ENTRADA "./pipex entrada "cmd 1" "cmd2" "cmd3" ... "
// cmd1 = "ls -la"
// ["ls", "-la"]
// split var_de_entorno (lo de PATH)
// iteramos iz->dir a ver si hay el binario si si prefix
// pid = fork()
// arg = ["(PATH)/ls", "-la"]
// execve(arg[0], arg, var_de_enotorno);







// */

// void	exec(char *cmd, char **env)
// {
// 	char	**s_cmd;
// 	char	*path;

// 	s_cmd = ft_split(cmd, ' ');
// 	path = get_path(s_cmd[0], env);
// 	if (execve(path, s_cmd, env) == -1)
// 	{
// 		ft_putstr_fd("pipex: command not found: ", 2);
// 		ft_putendl_fd(s_cmd[0], 2);
// 		ft_free_tab(s_cmd);
// 		exit(0);
// 	}
// }

// void	here_doc_put_in(char **av, int *p_fd)
// {
// 	char	*ret;

// 	close(p_fd[0]);
// 	while (1)
// 	{
// 		ret = get_next_line(0);
// 		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
// 		{
// 			free(ret);
// 			exit(0);
// 		}
// 		ft_putstr_fd(ret, p_fd[1]);
// 		free(ret);
// 	}//esta función escribe el heredoc en el fd de la pipe
// }//hasta que encuentra el delimitador y libera mientras

// void	here_doc(char **av)
// {
// 	int		p_fd[2];
// 	pid_t	pid;

// 	if (pipe(p_fd) == -1)
// 		exit(0);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(0);
// 	if (!pid)
// 		here_doc_put_in(av, p_fd);
// 	else
// 	{
// 		close(p_fd[1]);
// 		dup2(p_fd[0], 0);
// 		wait(NULL);
// 	}
// }

// void	do_pipe(char *cmd, char **env)
// {
// 	pid_t	pid;
// 	int		p_fd[2];

// 	if (pipe(p_fd) == -1)
// 		exit(0);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(0);
// 	if (!pid)
// 	{
// 		close(p_fd[0]);
// 		dup2(p_fd[1], 1);
// 		exec(cmd, env);
// 	}
// 	else
// 	{
// 		close(p_fd[1]);
// 		dup2(p_fd[0], 0);
// 	}
// }

// int	main(int ac, char **av, char **env)
// {
// 	int		i;
// 	int		fd_in;
// 	int		fd_out;

// 	if (ac < 5)
// 		exit_handler(1);
// 	if (ft_strcmp(av[1], "here_doc") == 0)
// 	{
// 		if (ac < 6)
// 			exit_handler(1);
// 		i = 3;
// 		fd_out = open_file(av[ac - 1], 2);
// 		here_doc(av);
// 	}
// 	else
// 	{
// 		i = 2;
// 		fd_in = open_file(av[1], 0);
// 		fd_out = open_file(av[ac - 1], 1);
// 		dup2(fd_in, 0);
// 	}
// 	while (i < ac - 2)
// 		do_pipe(av[i++], env);
// 	dup2(fd_out, 1);
// 	exec(av[ac - 2], env);
// }

// char	*my_getenv(char *name, char **env)
// {//toma todas las variables hasta antes del igual
// //luego las compara con lo que devuelve la función de abajo
// 	int		i;
// 	int		j;
// 	char	*sub;

// 	i = 0;
// 	while (env[i])
// 	{
// 		j = 0;
// 		while (env[i][j] && env[i][j] != '=')
// 			j++;
// 		sub = ft_substr(env[i], 0, j);
// 		if (ft_strcmp(sub, name) == 0)
// 		{
// 			free(sub);
// 			return (env[i] + j + 1);
// 		}
// 		free(sub);
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*get_path(char *cmd, char **env)
// {
// 	int		i;
// 	char	*exec;
// 	char	**allpath;
// 	char	*path_part;
// 	char	**s_cmd;

// 	i = -1;
// 	allpath = ft_split(my_getenv("PATH", env), ':');//separa todas las rutas de path
// 	s_cmd = ft_split(cmd, ' ');//
// 	while (allpath[++i])
// 	{
// 		path_part = ft_strjoin(allpath[i], "/");
// 		exec = ft_strjoin(path_part, s_cmd[0]);
// 		free(path_part);
// 		if (access(exec, F_OK | X_OK) == 0)
// 		{
// 			ft_free_tab(s_cmd);
// 			return (exec);
// 		}
// 		free(exec);
// 	}
// 	ft_free_tab(allpath);
// 	ft_free_tab(s_cmd);
// 	return (cmd);
// }