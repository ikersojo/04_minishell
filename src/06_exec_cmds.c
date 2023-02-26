/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:39 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/26 18:13:10 by isojo-go         ###   ########.fr       */
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

void	ft_exec_cmds(t_data *data)
{
	t_cmd	*tmp;
	int		status;
	int		tempfd;

	tmp = data->cmd;
	while (tmp)
	{
		status = 0;
		// if (tmp->is_var == 1)
		// 	status = ft_addvar(data, tmp->str);
		if (tmp->next && tmp->next->next && tmp->next->is_pipe)
		{
			if (tmp->is_builtin)
			{
				tempfd = open(".tempfd", O_RDWR | O_CREAT | O_TRUNC, 0666);
				if (tmp->next->next->infd == STDIN_FILENO)
					tmp->next->next->infd = tempfd;
				if (tmp->outfd == STDOUT_FILENO)
				{
					tmp->outfd = tempfd;
					status = ft_launch_piped_builtin(tmp->str, tmp->infd, tmp->outfd, data);
				}
				else
				{
					status = ft_launch_builtin(tmp->str, tmp->infd, tmp->outfd, data);
				}
			}
			else if (tmp->is_exec)
				status = ft_launch_piped_process(tmp->str, tmp->infd, tmp->outfd, data);
		}
		else
		{
			if (tmp->is_builtin)
				status = ft_launch_builtin(tmp->str, tmp->infd, tmp->outfd, data);
			else if (tmp->is_exec)
				status = ft_launch_process(tmp->str, tmp->infd, tmp->outfd, data);
		}
		setenv_local(data->vars, "?", ft_itoa(status), 1);
		tmp = tmp->next;
	}
}
