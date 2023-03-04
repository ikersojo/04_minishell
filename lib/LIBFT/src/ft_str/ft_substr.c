/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:27:47 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/22 09:57:22 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/* DESCRIPTION:
Allocates (with malloc) and returns a new substring from the string s. The
substring begins at index start and is of size len. If start and len aren’t
refering to a valid substring, the behavior is undefined.
If the allocation fails, the function returns NULL.
---------------------------------------------------------------------------- */
char	*ft_substr(const char *s, int start, int len)
{
	char	*sub;
	int		i;

	if (s == NULL || len == 0 || ft_strlen(s) < start)
		return (NULL);
	if ((ft_strlen(s) - start) < len)
		len = ft_strlen(s) - start;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	s = s + start;
	i = 0;
	while (*s && i < len)
	{
		*(sub + i) = *s;
		i++;
		s++;
	}
	*(sub + i) = '\0';
	return (sub);
}
