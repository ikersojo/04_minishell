/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_02_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:26:53 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/26 21:51:11 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	env_builtin(t_vars **env, char **cmd)
{
	if (ft_strcmp(cmd[0], "env"))
		return (!printf("RTFM: Undefined error.\n"));
	if (cmd[1])
		return (1);
	while (env)
	{
		printf("%s=%s\n", (*env)->name, (*env)->val);
		*env = (*env)->next;
	}
	return (0);
}
