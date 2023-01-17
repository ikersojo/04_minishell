/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:25:55 by isojo-go          #+#    #+#             */
/*   Updated: 2022/12/13 20:32:46 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/* DESCRIPTION:
The strcat() function appends the src string to the dest string, overwriting
the terminating null byte at the end of dest, and then adds a terminating null
byte.
---------------------------------------------------------------------------- */
char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (*(dest + i))
		i++;
	while (*src)
		*(dest + i++) = *src++;
	*(dest + i) = '\0';
	return (dest);
}
