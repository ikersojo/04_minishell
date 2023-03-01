/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_01_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:50:01 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/26 22:10:38 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strjoin_arr(char **arr, char *del)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (arr[i])
	{
		len += ft_strlen(arr[i]);
		i++;
	}
	str = malloc(sizeof(char) * (len + i));
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

/*
 * Given a route, it returns the full route.
 * 		Example:
 * 			./a/b/../c/./d -> /a/c/d
 */
static char	*ft_route_parser(char *route)
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

/*
 * Check if user has permissions over a path.
 * 		Returns:
 * 			0: False
 * 			1: True
 */
static int	ft_check_dir_permission(char *path)
{
	if (access(path, F_OK) == -1)
		return (!printf("cd: Directory does not exist\n"));
	if (access(path, R_OK) == -1)
		return (!printf("cd: Access denied\n"));
	return (1);
}

/*
 * Automatically sets OLDPWD and sets PWD to given path.
 */
static void	ft_set_pwd(t_vars **env, char *path)
{
	setenv_local(*env, "OLDPWD", getenv_local(*env, "PWD")->val,
		1);
	setenv_local(*env, "PWD", path, 1);
}

/*
 * Build relative path from current path and new path.
 */
static char	*ft_build_rel_path(char *current, char *new)
{
	char	*pre_rel_path;
	char	*rel_path;

	pre_rel_path = ft_strjoin(current, "/");
	rel_path = ft_strjoin(pre_rel_path, new);
	pre_rel_path = ft_free_null(pre_rel_path);
	return (ft_route_parser(rel_path));
}

/*
 * This builtin is ultimately the way that all user-visible commands should
 * change the current working directory.
 */
int	ft_cd_builtin(t_vars **env, char **cmd)
{
	char	*rel_path;

	if (ft_strcmp(cmd[0], "cd"))
		return (!printf("RTFM: Undefined error.\n"));
	if (cmd[1] && cmd[2])
		return (!printf("pwd: Too many arguments\n"));
	if (!cmd[1])
	{
		if (!ft_check_dir_permission(getenv_local(*env, "HOME")->val))
			return (0);
		ft_set_pwd(env, getenv_local(*env, "HOME")->val);
	}
	if (cmd[1][0] == '/' && ft_check_dir_permission(cmd[1]))
		ft_set_pwd(env, cmd[1]);
	else if (cmd[1][0] != '/')
	{
		rel_path = ft_build_rel_path(getenv_local(*env, "PWD")->val,
				cmd[1]);
		if (ft_check_dir_permission(rel_path))
			ft_set_pwd(env, rel_path);
		free(rel_path);
	}
	else
		return (0);
	return (!chdir(getenv_local(*env, "PWD")->val));
}

/*
 * Print the name of the current working directory.
 * 		Params:
 * 			env: Current environment linked list
 * 			cmd: Command as an array of Strings
 * 		Returns:
 * 			 0: On Success
 * 			>0: On Failure
 */
int	ft_pwd_builtin(t_vars **env, char **cmd)
{
	if (ft_strcmp(cmd[0], "pwd"))
		return (printf("RTFM: Undefined error.\n"));
	if (cmd[1])
		return (printf("pwd: Too many arguments\n"));
	return (!printf("%s\n", getenv_local(*env, "PWD")->val));
}
