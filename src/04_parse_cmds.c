/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:07 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/07 09:45:26 by isojo-go         ###   ########.fr       */
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
	new->par_lvl = 0;
	new->is_outfd = 0;
	new->is_infd = 0;
	new->is_par = 0;
	new->is_and = 0;
	new->is_or = 0;
	new->is_pipe = 0;
	new->is_var = 0;
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
	else if (*str == '(' || *str == ')')
		new->is_par = 1;
	else if (*str == '&' && *(str + 1) == '&')
		new->is_and = 1;
	else if (*str == '|')
	{
		if (*(str + 1) == '|')
			new->is_or = 1;
		else
			new->is_pipe = 1;
	}
	else if (ft_is_var_definition(str))
		new->is_var = 1;
	else
		new->is_exec = 1;
	new->next = NULL;
	return (new);
}

static t_cmd	*ft_cmdlast(t_cmd *cmd, int *par_lvl)
{
	if (cmd == NULL)
		return (NULL);
	while (cmd->next)
	{
		if (*cmd->str == '(')
			*par_lvl += 1;
		else if (*cmd->str == ')')
			*par_lvl -= 1;
		cmd = cmd->next;
	}
	if (*cmd->str == '(')
		*par_lvl += 1;
	else if (*cmd->str == ')')
		*par_lvl -= 1;
	return (cmd);
}

static void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;
	int		par_lvl;

	par_lvl = 0;
	if (new && cmd)
	{
		if (*cmd == NULL)
			*cmd = new;
		else
		{
			tmp = ft_cmdlast(*cmd, &par_lvl);
			new->par_lvl = par_lvl;
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
		else if (ft_ischarset(*(data->ex_input + i), "()"))
		{
			str = ft_substr(data->ex_input, i, 1);
			i++;
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
