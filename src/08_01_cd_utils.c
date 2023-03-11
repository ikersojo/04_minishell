/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_01_cd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalient <mvalient@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:12:50 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/04 20:17:19 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * Automatically sets OLDPWD and sets PWD to given path.
 */
void	ft_set_pwd(t_vars **env, char *path)
{
	if (ft_getenv_local(*env, "PWD") != NULL)
		ft_setenv_local(*env, "OLDPWD", ft_getenv_local(*env, "PWD")->val, 1);
	ft_setenv_local(*env, "PWD", path, 1);
}

/*
 * Given a route, it returns the full route.
 * 		Example:
 * 			./a/b/../c/./d -> /a/c/d
 */
char	*ft_route_parser(char *route)
{
	char	**split;
	char	*full_route;
	char	*temp_route;
	int		i;

	i = 0;
	split = ft_split(route, '/');
	while (split[i])
	{
		if (!ft_strcmp(split[i], "."))
			split[i] = ft_free_null(split[i]);
		else if (!ft_strcmp(split[i], ".."))
		{
			split[i] = ft_free_null(split[i]);
			if (i > 0)
				split[i - 1] = ft_free_null(split[i - 1]);
		}
		i++;
	}
	temp_route = ft_strjoin_arr(split, "/");
	full_route = ft_strjoin("/", temp_route);
	free(temp_route);
	free(split);
	free(route);
	return (full_route);
}

char	*ft_strjoin_arr(char **arr, char *del)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!arr[i])
		return (malloc(1));
	while (arr[i])
	{
		len += ft_strlen(arr[i]);
		i++;
	}
	str = ft_calloc(1, sizeof(char) * (len + i));
	i = 0;
	while (arr[i])
	{
		ft_strcat(str, arr[i]);
		if (arr[i + 1])
			ft_strcat(str, del);
		free(arr[i]);
		i++;
	}
	return (str);
}

void	*ft_free_null(void *ptr)
{
	free(ptr);
	return (NULL);
}
