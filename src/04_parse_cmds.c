/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:53:58 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/18 10:39:22 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_free_cmd(char ***cmd)
{
	int		i;

	i = 0;
	while (*((*cmd) + i))
		free (*((*cmd) + i++));
	free ((*cmd));
}

void	ft_last_exec(t_data *data)
{
	t_cmd	*tmp;
	char	**cmd;
	char	*cmd_path;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->is_exec == 1)
		{
			cmd = ft_get_args(tmp->str);
			if (*(*(cmd + 0)) == '/' || *(*(cmd + 0)) == '.')
				ft_setenv_local(data->vars, "_", *(cmd + 0), 1);
			else
			{
				cmd_path = ft_get_path(*(cmd + 0), data);
				if (cmd_path != NULL)
				{
					ft_setenv_local(data->vars, "_", cmd_path, 1);
					free(cmd_path);
				}
			}
			ft_free_cmd(&cmd);
		}
		tmp = tmp->next;
	}
}

void	ft_parse(t_data *data)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
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
			str = ft_substr(data->ex_input, i,
					ft_endsub(data->ex_input, i, "()<>|&"));
			i += ft_endsub(data->ex_input, i, "()<>|&");
		}
		if (ft_strcmp(str, " ") != 0)
			ft_cmdadd_back(&data->cmd, ft_cmdnew(ft_strtrim(str, " \t"), j++));
		free (str);
	}
}
