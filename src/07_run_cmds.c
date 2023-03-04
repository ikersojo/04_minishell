/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_run_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:32:55 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/04 18:47:34 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_launch_piped_process(char *str, int infd, int outfd, t_data *data)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	(void)outfd;
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
		ft_signal_handler(ft_child_signals);
		close(*(fd + 0));
		dup2(*(fd + 1), STDOUT_FILENO);
		dup2(infd, STDIN_FILENO);
		ft_free_custom_envp(data);
		data->custom_envp = ft_gen_envp(data);
		ft_run_command(str, data, data->custom_envp);
		return (EXIT_FAILURE);
	}
}

int	ft_launch_process(char *str, int infd, int outfd, t_data *data)
{
	pid_t	pid;
	int		status;

	dup2(outfd, STDOUT_FILENO);
	dup2(infd, STDIN_FILENO);
	pid = fork();
	if (pid == -1)
		ft_exit_w_error("errno");
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (outfd != STDOUT_FILENO)
			close(outfd);
		if (infd != STDIN_FILENO)
			close (infd);
		dup2(data->baseline_infd, STDIN_FILENO);
		dup2(data->baseline_outfd, STDOUT_FILENO);
		return (WEXITSTATUS(status));
	}
	else
	{
		ft_signal_handler(ft_child_signals);
		ft_free_custom_envp(data);
		data->custom_envp = ft_gen_envp(data);
		ft_run_command(str, data, data->custom_envp);
		return (EXIT_FAILURE);
	}
}
