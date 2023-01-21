/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:18:26 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/21 18:19:42 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* DESCRIPTION:
Returns the position of the variable varname in the data->vars array.
if the variable is not found returns -1.
---------------------------------------------------------------------------- */
int	ft_var_pos(t_data *data, char *varname)
{
	int	i;

	i = 0;
	while ((data->vars + i)->name)
	{
		if (ft_strcmp(varname, (data->vars + i)->name) == 0)
			return (i);
		i++;
	}
	return (-1);
}
