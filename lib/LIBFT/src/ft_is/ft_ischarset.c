/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischarset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 07:52:09 by isojo-go          #+#    #+#             */
/*   Updated: 2022/09/22 08:16:38 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION:
The function tests if the character c is contained within the character that
are contained in the string set.
The function returns zero if the character tests false and returns non-zero if
the character tests true.
---------------------------------------------------------------------------- */
int	ft_ischarset(char c, const char *set)
{
	int	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}
