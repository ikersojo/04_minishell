/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:47:13 by isojo-go          #+#    #+#             */
/*   Updated: 2022/11/18 22:48:17 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION:
The function returns the max value of the integers provided as arguments.
---------------------------------------------------------------------------- */
int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
