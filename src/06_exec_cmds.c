/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:39 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/24 15:49:47 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



static int	ft_addvar(t_data *data, char *s) // ver si la tenemos que quitar
{
	int		loc;
	char	*aux;
	char	*name;
	char	*val;

	loc = ft_strfind(s, '=');
	aux = ft_substr(s, 0, loc);
	name = ft_strtrim(aux, " \t");
	free (aux);
	aux = ft_substr(s, loc + 1, ft_strlen(s) - loc);
	val = ft_strtrim(aux, " \t");
	free (aux);
	return (setenv_local(data->vars, name, val, 1));
}

void	ft_exec_cmds(t_data *data)
{
	t_cmd	*temp;
	int		status;

	ft_setup_redir(data);
	temp = data->cmd;
	while (temp)
	{
		if (temp->is_var == 1)
			status = ft_addvar(data, temp->str);
		if (temp->is_builtin)
		{
			if (ft_starts_with(temp->str, "cd"))
				status = ft_run_builtin(temp->str, data, cd_builtin);
			if (ft_starts_with(temp->str, "pwd"))
				status = ft_run_builtin(temp->str, data, pwd_builtin);
			if (ft_starts_with(temp->str, "echo"))
				status = ft_run_builtin(temp->str, data, echo_builtin);
			if (ft_starts_with(temp->str, "exit"))
				ft_free_all(data);
		}
		if (temp->is_exec)
		{
			if (temp->next && temp->next->is_pipe)
				status = ft_launch_piped_process(temp->str, temp->infd, temp->outfd, data);
			else
				status = ft_launch_process(temp->str, temp->infd, temp->outfd, data);
		}
		setenv_local(data->vars, "?", ft_itoa(status), 1);
		temp = temp->next;
	}
}
