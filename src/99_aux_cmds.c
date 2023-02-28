/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:05:05 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/28 22:04:47 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_is_builtin(char *str)
{

	if (ft_starts_with(str, "echo"))
		return (1);
	if (ft_starts_with(str, "cd"))
		return (1);
	if (ft_starts_with(str, "pwd"))
		return (1);
	if (ft_starts_with(str, "export"))
		return (1);
	if (ft_starts_with(str, "unset"))
		return (1);
	if (ft_starts_with(str, "env"))
		return (1);
	if (ft_starts_with(str, "exit"))
		return (1);
	return (0);
}

static void	ft_init_cmd(t_cmd *new, char *str, int index)
{
	new->str = str;
	new->index = index;
	new->infd = STDIN_FILENO;
	new->outfd = STDOUT_FILENO;
	new->is_exec = 0;
	new->is_outfd = 0;
	new->is_infd = 0;
	new->is_pipe = 0;
	new->is_builtin = 0;
}

t_cmd	*ft_cmdnew(char *str, int index)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	ft_init_cmd(new, str, index);
	if (*str == '>')
		new->is_outfd = 1;
	else if (*str == '<')
		new->is_infd = 1;
	else if (*str == '|')
		new->is_pipe = 1;
	else if (ft_is_builtin(str))
		new->is_builtin = 1;
	else
		new->is_exec = 1;
	new->next = NULL;
	return (new);
}

static t_cmd	*ft_cmdlast(t_cmd *cmd)
{
	if (cmd == NULL)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	if (new && cmd)
	{
		if (*cmd == NULL)
			*cmd = new;
		else
		{
			tmp = ft_cmdlast(*cmd);
			tmp->next = new;
		}
	}
}
