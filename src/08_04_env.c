/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_04_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:26:53 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/28 22:49:08 by isojo-go         ###   ########.fr       */
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
		printf("%s=%s\n", tmp->name, tmp->val);
		tmp = tmp->next;
	}
	return (0);
}
