/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:18:26 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/30 23:17:07 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_get_var(t_data *data, char *name)
{
	t_vars	*temp;
	char	*str;

	temp = data->vars;
	while (temp)
	{
		if (ft_strcmp(name, temp->name) == 0)
		{
			str = ft_strdup(temp->val);
			return (str);
		}
		temp = temp->next;
	}
	str = ft_strdup("unknown");
	return (str);
}

int	ft_endsub(char *str, int i, char *charset)
{
	int	j;

	j = 0;
	while (*(str + j + i))
	{
		if (ft_ischarset(*(str + j + i), charset))
		{
			if (j == 0)
			{
				if(*(str + j + i + 1) == *(str + j + i))
					return (2);
				return (1);
			}
			else
				break;
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
		if (ft_isspace(*(str + i + j)) || ft_ischarset(*(str + i + j), "<>)\"\'}]"))
			break ;
		j++;
	}	
	return (j);
}

void	ft_clear_screen(void)
{
	system("clear");
	ft_putstr_fd(GREEN, 1);
	ft_putstr_fd("                                                     \n", 1);
	ft_putstr_fd("           :::      ::::::::                         \n", 1);
	ft_putstr_fd("         :+:      :+:    :+:                         \n", 1);
	ft_putstr_fd("       +:+ +:+         +:+                           \n", 1);
	ft_putstr_fd("     +#+  +:+       +#+        \t\tminishell 42 by:  \n", 1);
	ft_putstr_fd("   +#+#+#+#+#+   +#+           \t\tmvalient          \n", 1);
	ft_putstr_fd("        #+#    #+#             \t\tisojo-go          \n", 1);
	ft_putstr_fd("       ###   ########.fr                             \n", 1);
	ft_putstr_fd("                                                     \n", 1);
	ft_putstr_fd(DEF_COLOR, 1);
}

int	ft_inside(char *str, int i, char c)
{
	int	j;
	int	count;

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
