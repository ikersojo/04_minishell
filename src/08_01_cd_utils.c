/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_01_cd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalient <mvalient@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:12:50 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/15 23:08:55 by mvalient         ###   ########.fr       */
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
	if (!split[0])
		return (free(split), free(route), ft_strdup("/"));
	temp_route = ft_strjoin_arr(split, "/", i);
	full_route = ft_strjoin("/", temp_route);
	return (free(temp_route), free(split), free(route), full_route);
}

char	*ft_strjoin_arr(char **arr, char *del, int length)
{
	char	*str;
	int		i;
	int		len;

	len = 0;
	if (!arr[0])
		return (malloc(1));
	i = -1;
	while (arr[++i])
		len += ft_strlen(arr[i]);
	str = ft_calloc(1, sizeof(char) * (len + (length * 2) + 1));
	i = 0;
	while (length--)
	{
		if (arr[i])
			ft_strcat(str, arr[i]);
		if (arr[i])
			free(arr[i]);
		if (arr[i + 1])
			ft_strcat(str, del);
		i++;
	}
	return (str);
}

void	*ft_free_null(void *ptr)
{
	free(ptr);
	return (NULL);
}

/*
 * Check if user has permissions over a path.
 * 		Returns:
 * 			0: False
 * 			1: True
 */
int	ft_check_dir_permission(char *path)
{
	if (access(path, F_OK) == -1)
		return (!printf("cd: Directory does not exist\n"));
	if (access(path, R_OK) == -1)
		return (!printf("cd: Access denied\n"));
	return (1);
}
