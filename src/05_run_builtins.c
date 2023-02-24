/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_run_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:01:54 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/24 13:51:55 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_run_builtin(char *full_cmd, t_data *data, int (*builtin)(t_vars *, char **))
{
	char	**cmd;
	int		i;
	int		error_flag;

	error_flag = 0;
	cmd = ft_get_args(full_cmd);
	if (builtin(data->vars, cmd) == -1)
		error_flag = 1;
	i = 0;
	while (*(cmd + i))
		free (*(cmd + i++));
	free (cmd);
	return (error_flag);
}
