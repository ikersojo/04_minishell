/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 22:24:13 by isojo-go          #+#    #+#             */
/*   Updated: 2022/11/23 16:05:47 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/* DESCRIPTION:
The strcmp() function lexicographically compares the null-terminated strings s1
and s2.
It return an integer greater than, equal to, or less than 0, according as the
string s1 is greater than, equal to, or less than the string s2.
The comparison is done using unsigned characters.
---------------------------------------------------------------------------- */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (*(s1 + i) && *(s2 + i) && *(s1 + i) == *(s2 + i))
		i++;
	return ((unsigned char)(*(s1 + i)) - (unsigned char)(*(s2 + i)));
}
