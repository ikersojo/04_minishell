/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalient <mvalient@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:37:00 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/14 21:21:10 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * For  each  name, remove the corresponding variable or function from the
 * environment.
 *
 * Returns
 * 		0: On Failure
 * 		1: On Success
 */
int	unset_builtin(t_vars *env, char **cmd)
{
	int	i;
	int status;

	if (!ft_strcmp(cmd[0], "unset"))
		return (!printf("RTFM: Undefined error.\n"));
	i = 0;
	status = 0;
	while (cmd[++i])
		status += setenv_local(env, cmd[1], "", 1);
	return (!status);
}