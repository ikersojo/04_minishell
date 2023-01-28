/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_exec_cmds_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:39 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/28 16:58:11 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_get_path(char *cmd, char **envp)
{
	int		i;
	char	**path_tab;
	char	*path;
	char	*aux;

	i = 0;
	while (ft_strnstr(*(envp + i), "PATH", 4) == NULL)
		i++;
	path_tab = ft_split(*(envp + i), ':');
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

static void	ft_run_command(char *arg, char **envp)
{
	char	**cmd;
	char	*cmd_path;
	int		i;
	int		error_flag;

	error_flag = 0;
	cmd = ft_split(arg, ' ');
	cmd_path = ft_get_path(*(cmd + 0), envp);
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

void	ft_launch_process(char *str, char **envp, int outfd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_exit_w_error("errno");
	if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		if (outfd != 1)
			dup2(outfd, STDOUT_FILENO);
		ft_run_command(str, envp);
	}
}

char	*ft_filename(char *str)
{
	int	i;

	i = 0;
	while (ft_ischarset(*(str + i),"<>") || ft_isspace(*(str + i)))
		i++;
	return (str + i);
}

void	ft_exec_cmds(t_data *data, char **envp)
{
	t_cmd	*temp;
	int		outfd;
	
	temp = data->cmd;
	while (temp)
	{
		if (temp->next != NULL && temp->next->is_outfd == 1) // si hay que redirigir salida
		{
			if (*(temp->next->str + 1) == '>')
				outfd = open(ft_filename(temp->next->str),
					O_WRONLY | O_CREAT | O_APPEND, 0666);
			else
				outfd = open(ft_filename(temp->next->str),
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
		}
		else
			outfd = 1;
		if (*(temp->str) == '<') // si quremos redirigir el input
		{
			if (*(temp->str + 1) == '<')
				ft_heredoc(ft_filename(temp->str), outfd);
			else
				printf ("redirecting input... (WIP)\n"); // DEBUG
		}


		// if (next = |)


		if (!ft_ischarset(*(temp->str), "()<>|&")) // si es un comando a ejecutar
		{
			ft_launch_process(temp->str, envp, outfd);
		}
		temp = temp->next;
	}
}
