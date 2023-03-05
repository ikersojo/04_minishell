/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:07 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/05 17:53:58 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_last_exec(t_data *data)
{
	t_cmd	*tmp;
	char	**cmd;
	char	*cmd_path;
	int		i;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->is_exec == 1)
		{
			cmd = ft_get_args(tmp->str);
			if (*(*(cmd + 0)) == '/' || *(*(cmd + 0)) == '.')
				cmd_path = *(cmd + 0);
			else
				cmd_path = ft_get_path(*(cmd + 0), data);
			if (cmd_path != NULL)
				setenv_local(data->vars, "_", cmd_path, 1);
			free(cmd_path);
			i = 0;
			while (*(cmd + i))
				free (*(cmd + i++));
			free (cmd);
		}
		tmp = tmp->next;
	}
}

void	ft_parse(t_data *data) // norma: demasiadas líneas
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
		// ft_last_exec(data);
	}
	if (DEBUG == 1)
		printf("\033[0;92m\n    ----> INPUT PARSING OK!\n\033[0;39m");
}
