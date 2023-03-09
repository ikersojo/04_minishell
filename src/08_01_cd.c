/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_01_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:50:01 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/09 22:08:08 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	if (ft_getenv_local(*env, "PWD") != NULL)
		ft_setenv_local(*env, "OLDPWD", ft_getenv_local(*env, "PWD")->val, 1);
	ft_setenv_local(*env, "PWD", path, 1);
}

/*
 * Build relative path from current path and new path.
 */
static char	*ft_rel_path(char *current, char *new)
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

	if (cmd[1] && cmd[2])
		return (!printf("pwd: Too many arguments\n"));
	if (!cmd[1])
	{
		if (!ft_check_dir_permission(ft_getenv_local(*env, "HOME")->val))
			return (0);
		ft_set_pwd(env, ft_getenv_local(*env, "HOME")->val);
	}
	else if (cmd[1][0] == '/' && ft_check_dir_permission(cmd[1]))
		ft_set_pwd(env, cmd[1]);
	else if (cmd[1][0] != '/')
	{
		rel_path = ft_rel_path(ft_getenv_local(*env, "PWD")->val, cmd[1]);
		if (ft_check_dir_permission(rel_path))
			ft_set_pwd(env, rel_path);
		free(rel_path);
	}
	else
		return (0);
	return (!chdir(ft_getenv_local(*env, "PWD")->val));
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
	return (!printf("%s\n", ft_getenv_local(*env, "PWD")->val));
}
