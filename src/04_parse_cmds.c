/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:07 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/16 18:41:24 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	new->is_var = 0;
	new->is_builtin = 0;
}

static t_cmd	*ft_cmdnew(char *str, int index)
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
	else if (ft_is_var_definition(str))
		new->is_var = 1;
	//swithc si es uno de cada
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

static void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
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

void	ft_parse(t_data *data)
{
	int		i;
	int		index;
	t_cmd	*temp;
	char	*str;

	index = 0;
	i = 0;
	while (*(data->ex_input + i))
	{
		if (ft_ischarset(*(data->ex_input + i), "<>"))
		{
			str = ft_substr(data->ex_input, i, ft_endredir(data->ex_input, i));
			i += ft_endredir(data->ex_input, i);
		}
		else
		{
			str = ft_substr(data->ex_input, i, ft_endsub(data->ex_input, i, "()<>|&"));
			i += ft_endsub(data->ex_input, i, "()<>|&");
		}
		if (ft_strcmp(str, " ") != 0)
		{
			temp = ft_cmdnew(ft_strtrim(str, " \t"), index++);
			ft_cmdadd_back(&data->cmd, temp);
		}
		free (str);
	}
}
