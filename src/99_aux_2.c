/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:53:58 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/18 10:40:13 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_endsub(char *str, int i, char *charset)
{
	int	j;

	j = 0;
	while (*(str + j + i))
	{
		if (ft_ischarset(*(str + j + i), charset) && !ft_inquotes(str, j + i))
		{
			if (j == 0)
			{
				if (*(str + j + i + 1) == *(str + j + i))
					return (2);
				return (1);
			}
			else
				break ;
		}
		j++;
	}
	return (j);
}

int	ft_endredir(char *str, int i)
{
	int	j;

	j = 0;
	while (ft_ischarset(*(str + i + j), "<>"))
		j++;
	while (ft_isspace(*(str + i + j)))
		j++;
	while (*(str + i + j))
	{
		if (ft_isspace(*(str + i + j))
			|| ft_ischarset(*(str + i + j), "<>)\"\'}]"))
			break ;
		j++;
	}	
	return (j);
}

int	ft_inside(char *str, int i, char c)
{
	int	j;
	int	count;

	if (*(str + i) == c)
		return (0);
	count = 0;
	j = 0;
	while (j < i)
	{
		if (*(str + j) == c)
			count++;
		j++;
	}
	if (count % 2 != 0)
		return (1);
	return (0);
}

int	ft_inquotes(char *str, int i)
{
	if (ft_inside(str, i, '\"') || ft_inside(str, i, '\''))
		return (1);
	return (0);
}
