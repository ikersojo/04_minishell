/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_04_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:26:53 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/06 22:15:17 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	env_builtin(t_vars **env, char **cmd)
{
	t_vars	*tmp;

	if (ft_strcmp(cmd[0], "env"))
		return (!printf("RTFM: Undefined error.\n"));
	if (cmd[1])
		return (1);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "?"))
			printf("%s=%s\n", tmp->name, tmp->val);
		tmp = tmp->next;
	}
	return (0);
}
