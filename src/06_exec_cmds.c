/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:39 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/04 20:22:34 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_check_final_seq(t_data *data)
{
	t_cmd	*tmp;
	int		error_flag;
	int		expected;

	error_flag = 0;
	expected = 1;
	tmp = data->cmd;
	while (tmp)
	{
		if ((expected == 1 && (tmp->is_exec || tmp->is_builtin))
			|| (expected == -1 && tmp->is_pipe))
			expected *= -1;
		else
			error_flag = 1;
		if (tmp->is_builtin && tmp->infd != STDIN_FILENO)
			error_flag = 1;
		tmp = tmp->next;
	}
	if (expected == 1 || error_flag == 1)
	{
		printf(SYNTAX_ERROR);
		return (1);
	}
	return (0);
}

void	ft_exec_cmds(t_data *data)
{
	t_cmd	*tmp;
	int		status;
	char	*status_str;

	status = 1;
	if (ft_check_final_seq(data) == 1)
		return ;
	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->next && tmp->next->is_pipe
			&& tmp->next->next && tmp->next->next->infd == STDIN_FILENO)
		{
			if (tmp->is_builtin)
			{
				tmp->outfd = open(".tempfd", O_WRONLY | O_CREAT | O_TRUNC, 0666);
				status = ft_launch_builtin(tmp->str, tmp->infd, tmp->outfd, data);
				tmp->next->next->infd = open(".tempfd", O_RDONLY);
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
		status_str = ft_itoa(status);
		ft_setenv_local(data->vars, "?", status_str, 1);
		free(status_str);
		tmp = tmp->next;
	}
}
