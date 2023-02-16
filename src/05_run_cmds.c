/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_run_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:32:55 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/16 18:08:50 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_get_path(char *cmd, t_data *data)
{
	int		i;
	char	**path_tab;
	char	*path;
	char	*aux;

	i = 0;
	path_tab = ft_split(ft_get_var(data, "PATH"), ':');
	i = 0;
	while (*(path_tab + i))
	{
		aux = ft_strjoin(*(path_tab + i), "/");
		path = ft_strjoin(aux, cmd);
		free (aux);
		free (*(path_tab + i++));
		if (access(path, F_OK) == 0)
			break ;
	}
	while (*(path_tab + i))
		free (*(path_tab + i++));
	free (path_tab);
	return (path);
}

static char	**ft_get_args(char *arg)
{
	char	**cmd;
	int		i;
	char	*mod;

	mod = (char *)malloc(ft_strlen(arg) + 1);
	if (mod == NULL)
		return NULL;
	i = 0;
	while (*(arg + i))
	{
		if (*(arg + i) == ' ' && !ft_inquotes(arg, i))
			*(mod + i) = '+';
		else
			*(mod + i) = *(arg + i);
		i++;
	}
	*(mod + i) = '\0';
	cmd = ft_split(mod, '+');
	free(mod);
	return (cmd);
}

static void	ft_run_command(char *arg, t_data *data, char **envp)
{
	char	**cmd;
	char	*cmd_path;
	int		i;
	int		error_flag;

	error_flag = 0;
	cmd = ft_get_args(arg);
	if (*(*(cmd + 0)) == '/' || *(*(cmd + 0)) == '.')
		cmd_path = *(cmd + 0);
	else
		cmd_path = ft_get_path(*(cmd + 0), data);
	if (DEBUG == 1)
		ft_check_cmd(cmd_path, cmd);
	if (execve(cmd_path, cmd, envp) == -1)
		error_flag = 1;
	i = 0;
	while (*(cmd + i))
		free (*(cmd + i++));
	free (cmd);
	free (cmd_path);
	if (error_flag == 1)
		ft_exit_w_error("Command not found\n");
}

int	ft_launch_piped_process(char *str, t_data *data, char **envp)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		ft_exit_w_error("errno");
	pid = fork();
	if (pid == -1)
		ft_exit_w_error("errno");
	if (pid > 0)
	{
		close(*(fd + 1));
		dup2(*(fd + 0), STDIN_FILENO);
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	else
	{
		close(*(fd + 0));
		dup2(*(fd + 1), STDOUT_FILENO);
		ft_run_command(str, data, envp);
		return (EXIT_FAILURE);
	}
}

int	ft_launch_process(char *str, int outfd, t_data *data, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_exit_w_error("errno");
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (outfd != STDOUT_FILENO)
			close(outfd);
		return (WEXITSTATUS(status));
	}
	else
	{
		if (outfd != STDOUT_FILENO)
			dup2(outfd, STDOUT_FILENO);
		ft_run_command(str, data, envp);
		return (EXIT_FAILURE);
	}
}
