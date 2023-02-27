/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_02_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:26:53 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/26 22:12:48 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_export_list(t_vars *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->val);
		env = env->next;
	}
	return (0);
}

/*
 * The supplied names are marked for automatic export to the environment of
 * subsequently executed commands. If a variable name is followed by =word,
 * the value of the variable is set to word.  Export returns an exit status
 * of 0 unless an  invalid option is encountered, one of the names is not a
 * valid shell variable name.
 *
 * // TODO : Remove "=" handling from shell
 */
int	export_builtin(t_vars **env, char **cmd)
{
	int	i;

	i = 0;
	if (ft_strcmp(cmd[i++], "export"))
		return (!printf("RTFM: Undefined error.\n"));
	if (!cmd[i])
	{
		ft_export_list(*env);
	}
	while (cmd[i])
	{
		if (!ft_count_chars(cmd[i], '='))
			getenv_local(*env, cmd[i])->is_exp = 1;
		else
		{
			// TODO : Trim str by first = and sentenv with part1 and part2
		}
		i++;
	}
	return (0);
}
