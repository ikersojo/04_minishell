/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_samesign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:40:42 by isojo-go          #+#    #+#             */
/*   Updated: 2022/11/18 22:42:25 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION:
The function tests for if the sign of both integers passed as arguments have
the same sign.
The function returns zero if tests false and returns non-zero if tests true.
---------------------------------------------------------------------------- */
int	ft_is_samesign(int a, int b)
{
	if ((a >= 0 && b >= 0) || (a < 0 && b < 0))
		return (1);
	return (0);
}
