/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_00_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:53:58 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/18 10:39:46 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Print the arguments in list to standard output.  If the
 * first word is'-n', then don't print a trailing newline. */
int	ft_echo_builtin(t_vars **env, char **cmd)
{
	int	i;
	int	newline;

	(void)*env;
	i = 0;
	newline = 1;
	if (ft_strcmp(cmd[i], "echo"))
		return (printf("RTFM: Undefined error.\n"));
	while (cmd [++i] && !ft_strcmp(cmd[i], "-n"))
		newline = 0;
	while (cmd[i])
	{
		printf("%s", cmd[i++]);
		if (cmd[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (EXIT_SUCCESS);
}
