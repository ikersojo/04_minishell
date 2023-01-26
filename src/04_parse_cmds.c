/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:07 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/26 10:43:46 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_cmd	*ft_cmdnew(char *str, int index)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->index = index;
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
		if (i != 0 && ft_ischarset(*(data->ex_input + i - 1), "<>"))
		{
			str = ft_substr(data->ex_input, i, ft_endwrd(data->ex_input, i));
			i += ft_endwrd(data->ex_input, i);
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

void	ft_freecmd(t_data *data)
{
	t_cmd	*tmp;
	t_cmd	*current;

	tmp = data->cmd;
	while(tmp)
	{
		current = tmp;
		tmp = tmp->next;
		free (current->str);
		free (current);
	}
	data->cmd = NULL;
}
