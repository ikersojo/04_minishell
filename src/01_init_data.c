/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:43:22 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/05 12:56:12 by mvalient         ###   ########.fr       */
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
	int		l;
	char	*name;
	char	*value;
	int		flag;

	data->vars = ft_varsnew(ft_strdup("?"), ft_strdup("0"));
	if (!data->vars)
	{
		ft_free_all(data);
		ft_exit_w_error(MALLOC_ERROR);
	}
	i = -1;
	while (*(envp + (++i)))
	{
		l = ft_strfind(*(envp + i), '=');
		if (l != -1 && l != 0)
		{
			name = ft_substr(*(envp + i), 0, l);
			value = ft_substr(*(envp + i), l + 1, ft_strlen(*(envp + i)) - l);
			flag = setenv_local(data->vars, name, value, 0);
			free(name);
			free(value);
			if (flag == -1)
				ft_free_all(data);
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
	data->custom_envp = NULL;
	data->cmd= NULL;
	ft_import_envp(data, envp);
	data->baseline_infd = dup(STDIN_FILENO);
	data->baseline_outfd = dup(STDOUT_FILENO);
	if (DEBUG == 1)
		printf("\033[0;92m\n    ----> DATA INITIALIZATION OK!\n\033[0;39m");
	return (data);
}
