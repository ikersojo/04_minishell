/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_w_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:31:25 by isojo-go          #+#    #+#             */
/*   Updated: 2022/12/10 19:58:18 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/* DESCRIPTION:
Exits the program, outputting a string with the details on the error to STDOUT.
If str is "errno" the default description of error is displayed. Else, the
custom str will be used as description of the error.
---------------------------------------------------------------------------- */
void	ft_exit_w_error(char *str)
{
	if (ft_strcmp("errno", str) == 0)
	{
		perror("\033[31mError");
		ft_putstr_fd("\033[0;39m", 2);
	}
	else
	{
		ft_putstr_fd("\033[31mError: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\033[0;39m", 2);
	}
	exit(EXIT_FAILURE);
}
