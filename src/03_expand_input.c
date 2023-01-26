/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_expand_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:44:09 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/25 19:14:37 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_get_expanded_len(t_data *data)
{
	int	len;
	int	i;
	int	count;

	len = 0;
	i = 0;
	while ((data->vars + i)->name)
	{
		if (ft_strlen((data->vars + i)->name) > len)
			len = ft_strlen((data->vars + i)->name);
		i++;
	}
	count = ft_count_chars(data->input, '$');
	len = len * count + ft_strlen(data->input) + 1;
	return (len);
}

static int	ft_expand_var(t_data *data, int i, int j)
{
	int		k;
	char	*varname;
	int		pos;

	varname = (char *)malloc(sizeof(char) * (ft_strlen(data->input) + 1));
	if (!varname)
	{
		ft_free_all(data);
		ft_exit_w_error(MALLOC_ERROR);
	}
	ft_strlcpy(varname, data->input + i + 1, ft_endwrd(data->input, i));
	pos = ft_var_pos(data, varname);
	free(varname);
	k = 0;
	while (*((data->vars + pos)->val + k))
		*(data->ex_input + j++) = *((data->vars + pos)->val + k++);
	return (k);
}

void	ft_expand(t_data *data)
{
	int 	i;
	int		j;

	data->ex_input = (char *)malloc(sizeof(char) * ft_get_expanded_len(data));
	if (!data->ex_input)
	{
		ft_free_all(data);
		ft_exit_w_error(MALLOC_ERROR);
	}
	i = 0;
	j = 0;
	while(*(data->input + i))
	{
		if (*(data->input + i) == '$')
		{
			j += ft_expand_var(data, i, j);
			i += ft_endwrd(data->input, i);
		}
		else if (ft_isspace(*(data->input + i)))
		{
			if (!ft_isspace(*(data->input + i + 1)) && j != 0)
				*(data->ex_input + j++) = ' ';
			i++;
		}
		else
			*(data->ex_input + j++) = *(data->input + i++);
	}
	*(data->ex_input + j) = '\0';
	j--;
	while (j > 0 && *(data->ex_input + j) == ' ')
		*(data->ex_input + j--) = '\0';
}
