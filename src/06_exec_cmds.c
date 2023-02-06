/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:39 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/06 22:24:07 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_filename(char *str)
{
	int	i;

	i = 0;
	while (ft_ischarset(*(str + i),"<>") || ft_isspace(*(str + i)))
		i++;
	return (str + i);
}

static void	ft_setup_redir(t_data *data, char **envp)
{
	t_cmd	*temp;

	(void)envp;
	temp = data->cmd;
	while (temp)
	{
		if (temp->next && temp->next->is_outfd == 1)
		{
			printf ("\033[0;93m    redirecting output... \033[0;39m\n"); // DEBUG
			if (*(temp->next->str + 1) == '>')
				temp->outfd = open(ft_filename(temp->next->str),
					O_WRONLY | O_CREAT | O_APPEND, 0666);
			else
				temp->outfd = open(ft_filename(temp->next->str),
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (temp->outfd == -1)
				ft_exit_w_error("errno");
		}
		if (temp->is_infd && temp->next)
		{
			printf ("\033[0;93m    redirecting input... \033[0;39m\n"); // DEBUG
			if (*(temp->str + 1) == '<')
			{
				ft_heredoc(ft_filename(temp->str), temp->outfd);
				if(temp->outfd == STDOUT_FILENO)
					temp->next->infd = open(".tempfd", O_RDONLY);
			}
			else
				temp->next->infd = open(ft_filename(temp->str), O_RDONLY);
			if (temp->next->infd == -1)
				ft_exit_w_error("errno");
			dup2(temp->next->infd, STDIN_FILENO);
			close(temp->next->infd);
		}
		temp = temp->next;
	}
}

void	ft_exec_cmds(t_data *data, char **envp)
{
	t_cmd	*temp;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_exit_w_error("errno");
	if (pid > 0)
	{
		waitpid(pid, &data->last_status, 0);
		ft_mod_status(data, data->last_status);
		// printf("\033[0;93m    child process for execution completed (exit: %d)\033[0;39m\n", data->last_status); // DEBUG
	}
	else
	{
		ft_setup_redir(data, envp);
		// ft_show_parsed(data); //DEBUG
		temp = data->cmd;
		while (temp)
		{
			if(temp->is_exec == 1)
			{
				if (temp->next && temp->next->is_pipe)
					status = ft_launch_piped_process(temp->str, envp);
				else
					status = ft_launch_process(temp->str, temp->outfd, envp);
			}
			temp = temp->next;
		}
		// printf("\033[0;93m    exec loop completed\033[0;39m\n"); // DEBUG
		ft_free_all(data);
		exit(status);
	}
}
