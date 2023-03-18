/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_04_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:53:58 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/18 10:40:04 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env_builtin(t_vars **env, char **cmd)
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
			if (tmp->val != NULL)
				printf("%s=%s\n", tmp->name, tmp->val);
		tmp = tmp->next;
	}
	return (0);
}
