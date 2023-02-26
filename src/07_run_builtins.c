/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_run_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:01:54 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/26 19:32:01 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_run_builtin(char *full_cmd, t_data *data, int (*builtin)(t_vars *, char **))
{
	char	**cmd;
	int		i;
	int		error_flag;

	error_flag = 0;
	cmd = ft_get_args(full_cmd);
	if (builtin(data->vars, cmd) == -1)
		error_flag = 1;
	i = 0;
	while (*(cmd + i))
		free (*(cmd + i++));
	free (cmd);
	return (error_flag);
}


static int ft_options(char *str, t_data *data)
{
	int	status;

	if (ft_starts_with(str, "echo"))
		status = ft_run_builtin(str, data, echo_builtin);
	if (ft_starts_with(str, "cd"))
		status = ft_run_builtin(str, data, cd_builtin);
	if (ft_starts_with(str, "pwd"))
		status = ft_run_builtin(str, data, pwd_builtin);
	if (ft_starts_with(str, "export")) // ojo con el caracter '='
		status = 0; //TODO
	if (ft_starts_with(str, "unset"))
		status = 0; //TODO
	if (ft_starts_with(str, "env"))
		status = 0; //TODO
	return (status);
}

int	ft_launch_piped_builtin(char *str, int infd, int outfd, t_data *data) // algo falla...
{
	int		status;

	dup2(infd, STDIN_FILENO);
	dup2(outfd, STDOUT_FILENO);
	status = ft_options(str, data);
	if (infd != STDIN_FILENO)
		close (infd);
	dup2(data->baseline_infd, STDIN_FILENO);
	dup2(data->baseline_outfd, STDOUT_FILENO);
	if (ft_starts_with(str, "exit"))
		ft_free_all(data);
	return (status);
}

int	ft_launch_builtin(char *str, int infd, int outfd, t_data *data)
{
	int		status;

	dup2(outfd, STDOUT_FILENO);
	dup2(infd, STDIN_FILENO);
	status = ft_options(str, data);
	if (outfd != STDOUT_FILENO)
		close(outfd);
	if (infd != STDIN_FILENO)
		close (infd);
	dup2(data->baseline_infd, STDIN_FILENO);
	dup2(data->baseline_outfd, STDOUT_FILENO);
	if (ft_starts_with(str, "exit"))
		ft_free_all(data);
	return (status);
}