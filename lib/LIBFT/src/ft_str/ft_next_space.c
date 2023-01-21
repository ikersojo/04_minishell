/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:14:12 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/21 18:17:16 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/* DESCRIPTION:
Finds the next space character in the string str (starting from position i) and
returns the number of characters after position i.
If no space chracters are found on the string it returns the remaining amount
of chars until the end of the string.
---------------------------------------------------------------------------- */
int	ft_next_space(char *str, int i)
{
	int	len;

	len = 0;
	while (*(str + i))
	{
		if (ft_isspace(*(str + i)))
			return (len);
		len++;
		i++;
	}
	return (len);
}
