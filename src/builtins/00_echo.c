/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalient <mvalient@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:11:56 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/19 18:45:25 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Print the arguments in list to standard output.  If the
 * first word is'-n', then don't print a trailing newline. */
int	echo_builtin(t_vars *env, char **cmd)
{
	int	i;
	int	newline;

	(void)env;
	i = 0;
	newline = 1;
	if (ft_strcmp(cmd[i], "echo"))
		return (printf("RTFM: Undefined error.\n"));
	if (!ft_strcmp(cmd[++i], "-n"))
	{
		newline = 0;
		i++;
	}
	while (cmd[i])
		printf("%s ", cmd[i++]);
	if (newline)
		printf("\n");
	return (EXIT_SUCCESS);
}
