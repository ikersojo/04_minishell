/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_run_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalient <mvalient@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:01:54 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/20 18:03:26 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_run_builtin(char *full_cmd, t_data *data, int (*builtin)(t_vars *, char **))
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
	if (error_flag == 1)
		ft_exit_w_error("Builtin not found\n");
}
