/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuhexnbr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 07:35:19 by isojo-go          #+#    #+#             */
/*   Updated: 2022/10/11 21:20:30 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/* DESCRIPTION:
Outputs the unisgned integer n to the file descriptor fd in hexadecimal.
The function returns the number of characters printed.
---------------------------------------------------------------------------- */
int	ft_putuhexnbr_fd(size_t n, int fd, char cs)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_putuhexnbr_fd(n / 16, fd, cs);
	if ((cs == 'x') || (cs == 'p'))
		count += ft_putchar_fd("0123456789abcdef"[n % 16], fd);
	if (cs == 'X')
		count += ft_putchar_fd("0123456789ABCDEF"[n % 16], fd);
	return (count);
}
