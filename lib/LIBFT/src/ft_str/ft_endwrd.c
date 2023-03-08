/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endwrd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:14:12 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/08 19:57:36 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/* DESCRIPTION:
Finds the next space character in the string str (starting from position i) and
returns the number of characters after position i.
If no space chracters are found on the string it returns the remaining amount
of chars until the end of the string.
---------------------------------------------------------------------------- */
int	ft_endwrd(char *str, int i)
{
	int	start;

	start = i;
	while (*(str + i) && ft_isspace(*(str + i)))
		i++;
	if (*(str + i) == '$')
		i++;
	if (*(str + i) == '?')
		i++;
	while (*(str + i))
	{
		if (ft_isspace(*(str + i)) || ft_ischarset(*(str + i), "/:)\"\'}]?$-+"))
			return (i - start);
		i++;
	}
	return (i - start);
}
