/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalient <mvalient@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:11:56 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/01 23:30:03 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

typedef struct s_argument
{
	char				*argument;
	struct s_argument	*next;
}					t_argument;

/* Print the arguments in list to standard output.  If the
 * first word is'-n', then don't print a trailing newline. */
int	echo_builtin(t_argument *list)
{
	int	newline;

	newline = 1;
	if (!ft_strcmp(list->argument, "-n"))
	{
		newline = 0;
		list = list->next;
	}
	while (list)
	{
		// TODO: Maybe create function to just print a string.
		printf("%s ", list->argument);
		list = list->next;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}
