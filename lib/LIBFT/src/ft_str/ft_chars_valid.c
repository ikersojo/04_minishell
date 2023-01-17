/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chars_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:29:20 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/17 11:48:20 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/* DESCRIPTION:
The function checks if all the characters in string str are contained in the
string valid_chars.
It return 1 if the comparison tests true or 0 if tests false.
---------------------------------------------------------------------------- */
int	ft_chars_valid(char *str, char *valid_chars)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (!ft_ischarset(*(str + i++), valid_chars))
			return (0);
	}
	return (1);
}
