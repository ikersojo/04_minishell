/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:22:31 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/19 19:23:50 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION:
Finds the first instance of the char c in the string str and returns the
position in the string. If c is not found, returns -1.
---------------------------------------------------------------------------- */
int	ft_strfind(char *str, char c)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == c)
			return (i);
		i++;
	}
	return (-1);
}
