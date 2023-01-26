/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:39 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/26 12:37:45 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int g_outfd;

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

void	ft_launch_process(char *str, char **envp)
{
	pid_t	pid;
	// int		fd[2];
	int		status;

	// if (pipe(fd) == -1)
	// 	ft_exit_w_error("errno");
	pid = fork();
	if (pid == -1)
		ft_exit_w_error("errno");
	if (pid > 0)
	{
		// close(*(fd + 1));
		// dup2(*(fd + 0), STDIN_FILENO);
		waitpid(pid, &status, 0);
	}
	else
	{
		// close(*(fd + 0));
		// dup2(*(fd + 1), g_outfd);
		ft_run_command(str, envp);
	}
}

void	ft_exec_cmds(t_data *data, char **envp)
{
	t_cmd *temp;
	
	temp = data->cmd;
	while (temp)
	{
		if (!ft_ischarset(*(temp->str), "()<>|&"))
		{
			printf("executing cmd %d: %s\n", temp->index, temp->str);
			ft_launch_process(temp->str, envp);
		}
		temp = temp->next;
	}
}
