/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_01_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:50:01 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/15 23:12:21 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static int	ft_absolute_path(t_vars **env, char **cmd)
{
	int	flag;

	flag = 0;
	flag = ft_check_dir_permission(cmd[1]);
	if (flag)
		ft_set_pwd(env, cmd[1]);
	return (flag);
}

static int	ft_cd_builtin_two(t_vars **env, char **cmd)
{
	int		flag;
	char	*rel_path;

	flag = 0;
	if (!cmd[1])
	{
		if (!ft_getenv_local(*env, "HOME")
			|| !ft_check_dir_permission(ft_getenv_local(*env, "HOME")->val))
			return (!printf("cd: Home not defined\n"));
		ft_set_pwd(env, ft_getenv_local(*env, "HOME")->val);
		flag = 1;
	}
	else if (cmd[1][0] == '/')
		flag = ft_absolute_path(env, cmd);
	else if (cmd[1][0] != '/')
	{
		rel_path = ft_rel_path(ft_getenv_local(*env, "PWD")->val, cmd[1]);
		flag = ft_check_dir_permission(rel_path);
		if (flag)
			ft_set_pwd(env, rel_path);
		free(rel_path);
	}
	return (flag);
}

/*
 * This builtin is ultimately the way that all user-visible commands should
 * change the current working directory.
 */
int	ft_cd_builtin_one(t_vars **env, char **cmd)
{
	int		status;
	char	*rel_path;

	rel_path = getcwd(NULL, 0);
	if (ft_getenv_local(*env, "PWD") == NULL)
		ft_setenv_local(*env, "PWD", rel_path, 1);
	if (cmd[1] && cmd[2])
		return (!printf("cd: Too many arguments\n"));
	status = ft_cd_builtin_two(env, cmd);
	free(rel_path);
	chdir(ft_getenv_local(*env, "PWD")->val);
	return (!status);
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
