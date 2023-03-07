/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_run_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:01:54 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/07 18:22:36 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_run_builtin(char *full_cmd, t_data *data,
	int (*builtin)(t_vars **, char **))
{
	char	**cmd;
	int		i;
	int		error_flag;

	error_flag = 0;
	cmd = ft_get_args(full_cmd); // está generando buffer_overflow??
	if (builtin(&data->vars, cmd) == -1)
		error_flag = 1;
	i = 0;
	while (*(cmd + i))
		free (*(cmd + i++));
	free (cmd);
	return (error_flag);
}

static int	ft_options(char *str, t_data *data)
{
	int	status;

	if (ft_starts_with(str, "echo"))
		status = ft_run_builtin(str, data, ft_echo_builtin);
	if (ft_starts_with(str, "cd"))
		status = ft_run_builtin(str, data, ft_cd_builtin);
	if (ft_starts_with(str, "pwd"))
		status = ft_run_builtin(str, data, ft_pwd_builtin);
	if (ft_starts_with(str, "export"))
		status = ft_run_builtin(str, data, ft_export_builtin);
	if (ft_starts_with(str, "unset"))
		status = ft_run_builtin(str, data, ft_unset_builtin);
	if (ft_starts_with(str, "env"))
		status = ft_run_builtin(str, data, ft_env_builtin);
	return (status);
}

int	ft_launch_builtin(char *str, int infd, int outfd, t_data *data)
{
	int	status;

	if (infd != STDIN_FILENO)
		dup2(infd, STDIN_FILENO);
	if (outfd != STDOUT_FILENO)
		dup2(outfd, STDOUT_FILENO);
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
