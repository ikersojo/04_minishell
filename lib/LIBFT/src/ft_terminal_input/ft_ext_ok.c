/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ext_ok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:49:35 by isojo-go          #+#    #+#             */
/*   Updated: 2022/12/24 10:52:22 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/* DESCRIPTION:
Checks if the file extension of the filename provided is the provided one or
not. Return 1 if true or 0 if false.
---------------------------------------------------------------------------- */
int	ft_ext_ok(char *filename, char *ext)
{
	if (!ft_strnstr(filename + ft_strlen(filename) - ft_strlen(ext),
			ext, ft_strlen(ext)))
		return (0);
	return (1);
}
