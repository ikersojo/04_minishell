/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:18:26 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/26 22:35:48 by isojo-go         ###   ########.fr       */
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

int	ft_endsub(char *str, int i, char *charset)
{
	int	j;

	j = 0;
	while (*(str + j + i))
	{
		if (ft_ischarset(*(str + j + i), charset))
		{
			if (j == 0)
			{
				if(*(str + j + i + 1) == *(str + j + i))
					return (2);
				return (1);
			}
			else
				break;
		}
		j++;
	}
	return (j);
}

void	ft_clear_screen(void)
{
	system("clear");
	ft_putstr_fd(GREEN, 1);
	ft_putstr_fd("                                                     \n", 1);
	ft_putstr_fd("           :::      ::::::::                         \n", 1);
	ft_putstr_fd("         :+:      :+:    :+:                         \n", 1);
	ft_putstr_fd("       +:+ +:+         +:+                           \n", 1);
	ft_putstr_fd("     +#+  +:+       +#+       minishell 42 by:       \n", 1);
	ft_putstr_fd("   +#+#+#+#+#+   +#+            isojo-go             \n", 1);
	ft_putstr_fd("        #+#    #+#              mvalient             \n", 1);
	ft_putstr_fd("       ###   ########.fr                             \n", 1);
	ft_putstr_fd("                                                     \n", 1);
	ft_putstr_fd(DEF_COLOR, 1);

}