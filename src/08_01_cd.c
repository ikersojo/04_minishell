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

/*
 * Check if user has permissions over a path.
 * 		Returns:
 * 			0: False
 * 			1: True
 */
int	check_dir_permission(char *path)
{
	if (access(path, F_OK) == -1)
		return (!printf("cd: Directory does not exist\n"));
	if (access(path, R_OK) == -1)
		return (!printf("cd: Access denied\n"));
	return (1);
}

/*
 * This builtin is ultimately the way that all user-visible commands should
 * change the current working directory.
 * TODO : Might be interesting to create a route parser
 */
int	cd_builtin(t_vars **env, char **cmd)
{
	char	*rel_path;

	if (ft_strcmp(cmd[0], "cd"))
		return (!printf("RTFM: Undefined error.\n"));
	if (cmd[1] && cmd[2])
		return (!printf("pwd: Too many arguments\n"));
	if (!cmd[1])
	{
		if (!check_dir_permission(getenv_local(*env, "HOME")->val))
			return (0);
		setenv_local(*env, "OLDPWD", getenv_local(*env, "PWD")->val, 1);
		setenv_local(*env, "PWD", getenv_local(*env, "HOME")->val, 1);
	}
	else
	{
		if (cmd[1][0] == '/' && check_dir_permission(cmd[1]))
		{
			setenv_local(*env, "OLDPWD", getenv_local(*env, "PWD")->val, 1);
			setenv_local(*env, "PWD", cmd[1], 1);
		}
		else if (cmd[1][0] != '/')
		{
			rel_path = ft_strjoin(ft_strjoin(getenv_local(*env, "PWD")->val,
											 "/"), cmd[1]);
			if (check_dir_permission(rel_path))
			{
				setenv_local(*env, "OLDPWD", getenv_local(*env, "PWD")->val, 1);
				setenv_local(*env, "PWD", rel_path, 1);
			}
			free(rel_path);
		}
		else
			return (0);
	}
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
int	pwd_builtin(t_vars **env, char **cmd)
{
	if (ft_strcmp(cmd[0], "pwd"))
		return (printf("RTFM: Undefined error.\n"));
	if (cmd[1])
		return (printf("pwd: Too many arguments\n"));
	return (!printf("%s\n", getenv_local(*env, "PWD")->val));
}
