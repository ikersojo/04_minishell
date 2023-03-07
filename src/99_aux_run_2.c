/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_run_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:24:16 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/07 18:38:32 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_modified_args(char *arg)
{
	int		i;
	int		j;
	char	*mod;

	mod = (char *)malloc(ft_strlen(arg) + 1);
	if (mod == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (*(arg + i))
	{
		if (ft_ischarset(*(arg + i), "\"\'") && !ft_inquotes(arg, i))
			i++;
		else if (*(arg + i) == ' ' && !ft_inquotes(arg, i))
		{
			*(mod + j++) = '+';
			i++;
		}
		else
			*(mod + j++) = *(arg + i++);
	}
	*(mod + j) = '\0';
	return (mod);
}

char	**ft_get_args(char *arg)
{
	char	**cmd;
	char	*mod;

	if (arg == NULL)
		return (NULL);
	mod = ft_modified_args(arg);
	cmd = ft_split(mod, '+');
	free(mod);
	return (cmd);
}

static char	**ft_init_get_path(int *i, char **path, t_data *data)
{
	t_vars	*path_env;
	char	**path_tab;

	*path = NULL;
	path_env = ft_getenv_local(data->vars, "PATH");
	if (path_env == NULL)
		return (NULL);
	path_tab = ft_split(path_env->val, ':');
	*i = 0;
	return (path_tab);
}

char	*ft_get_path(char *cmd, t_data *data)
{
	int		i;
	char	**path_tab;
	char	*path;
	char	*aux;

	path_tab = ft_init_get_path(&i, &path, data);
	while (*(path_tab + i))
	{
		aux = ft_strjoin(*(path_tab + i), "/");
		path = ft_strjoin(aux, cmd);
		free (aux);
		free (*(path_tab + i++));
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	while (*(path_tab + i))
		free (*(path_tab + i++));
	free (path_tab);
	return (path);
}
