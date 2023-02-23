/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:43:22 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/23 23:29:00 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_export_all(t_vars *list)
{
	t_vars	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "?"))
			tmp->is_exp = 1;
		tmp = tmp->next;
	}
}

static void	ft_import_envp(t_data *data, char **envp)
{
	int		i;
	int		loc;

	data->vars = ft_varsnew(ft_strdup("?"), ft_strdup("0"));
	if (!data->vars)
	{
		ft_free_all(data);
		ft_exit_w_error(MALLOC_ERROR);
	}
	i = -1;
	while (*(envp + (++i)))
	{
		loc = ft_strfind(*(envp + i), '=');
		if (loc != -1 && loc != 0)
		{
			if (setenv_local(data->vars, ft_substr(*(envp + i), 0, loc),
					ft_substr(*(envp + i), loc + 1, ft_strlen(*(envp + i))
						- loc), 0) == -1)
			{
				ft_free_all(data);
				ft_exit_w_error(MALLOC_ERROR);
			}
		}
	}
	ft_export_all(data->vars);
}

t_data	*ft_init_data(char **envp)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_exit_w_error(MALLOC_ERROR);
	ft_import_envp(data, envp);
	data->baseline_infd = dup(STDIN_FILENO);
	data->baseline_outfd = dup(STDOUT_FILENO);
	if (DEBUG == 1)
		printf("\033[0;92m\n    ----> DATA INITIALIZATION OK!\n\033[0;39m");
	return (data);
}