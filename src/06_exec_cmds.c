/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:39 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/26 16:18:03 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static int	ft_addvar(t_data *data, char *s) // ver si la tenemos que quitar
// {
// 	int		loc;
// 	char	*aux;
// 	char	*name;
// 	char	*val;

// 	loc = ft_strfind(s, '=');
// 	aux = ft_substr(s, 0, loc);
// 	name = ft_strtrim(aux, " \t");
// 	free (aux);
// 	aux = ft_substr(s, loc + 1, ft_strlen(s) - loc);
// 	val = ft_strtrim(aux, " \t");
// 	free (aux);
// 	return (setenv_local(data->vars, name, val, 1));
// }

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

static int	ft_select_piped_builtin(char *str, int infd, int outfd, t_data *data) // algo falla...
{
	int		status;

	(void)outfd;
	dup2(infd, STDIN_FILENO);
	dup2(STDIN_FILENO, STDOUT_FILENO);
	status = ft_options(str, data);
	if (infd != STDIN_FILENO)
		close (infd);
	if (ft_starts_with(str, "exit"))
		ft_free_all(data);
	return (status);
}

static int	ft_select_builtin(char *str, int infd, int outfd, t_data *data)
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

void	ft_exec_cmds(t_data *data)
{
	t_cmd	*tmp;
	int		status;

	tmp = data->cmd;
	while (tmp)
	{
		// if (tmp->is_var == 1)
		// 	status = ft_addvar(data, tmp->str);
		if (tmp->next && tmp->next->next && tmp->next->is_pipe
			&& tmp->next->next->infd == STDIN_FILENO)
		{
			if (tmp->is_builtin)
				status = ft_select_piped_builtin(tmp->str, tmp->infd, tmp->outfd, data);
			else if (tmp->is_exec)
				status = ft_launch_piped_process(tmp->str, tmp->infd, tmp->outfd, data);
		}
		else
		{
			if (tmp->is_builtin)
				status = ft_select_builtin(tmp->str, tmp->infd, tmp->outfd, data);
			else if (tmp->is_exec)
				status = ft_launch_process(tmp->str, tmp->infd, tmp->outfd, data);
		}
		setenv_local(data->vars, "?", ft_itoa(status), 1);
		tmp = tmp->next;
	}
}
