/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:15:28 by isojo-go          #+#    #+#             */
/*   Updated: 2022/09/20 12:22:43 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION:
The isspace() function tests for the white-space characters. For any locale,
this includes the following standard characters:

``\t''``\n''``\v''``\f''``\r''`` ''

The value of the argument must be representable as an unsigned char or the
value of EOF.
The isspace() function returns zero if the character tests false and returns
non-zero if the character tests true.
---------------------------------------------------------------------------- */
int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
