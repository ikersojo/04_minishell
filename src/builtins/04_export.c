/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalient <mvalient@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:26:53 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/20 16:11:10 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * The supplied names are marked for automatic export to the environment of
 * subsequently executed commands. If a variable name is followed by =word,
 * the value of the variable is set to word.  Export returns an exit status
 * of 0 unless an  invalid option is encountered, one of the names is not a
 * valid shell variable name.
 *
 * // TODO : Remove "=" handling from shell
 */
int	export_builtin(t_vars *env, char **cmd)
{
	int	i;
	int status;

	i = 0;
	if (ft_strcmp(cmd[i++], "export"))
		return (!printf("RTFM: Undefined error.\n"));
	if (!cmd[i])
	{
		ft_export_list(env, cmd);
	}
	while (cmd[i])
	{
		if(!ft_count_chars(cmd[i], '='))
			getenv_local(env, cmd[i])->is_exp = 1;
		else
		{
			// TODO : Trim str by first = and sentenv with part1 and part2
		}
		i++;
	}
	return (0);
}

static int	ft_export_list(t_vars *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->val);
		env = env->next;
	}
	return (0);
}