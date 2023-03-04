/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_expand_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:44:09 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/04 20:30:38 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_get_expanded_len(t_data *data)
{
	int		len;
	int		n;
	t_vars	*temp;

	len = 0;
	temp = data->vars;
	while (temp)
	{
		if (ft_strlen(temp->name) > len)
			len = ft_strlen(temp->name);
		temp = temp->next;
	}
	n = ft_count_chars(data->input, '$') + ft_count_chars(data->input, '~');
	len = len * n + ft_strlen(data->input) + 1;
	return (len);
}

static int	ft_expand_var(t_data *data, int i, int j)
{
	int		k;
	char	*varname;
	char	*varvalue;

	if (*(data->input + i) == '~')
		varvalue = getenv_local(data->vars, "HOME")->val;
	else
	{
		varname = (char *)malloc(sizeof(char) * (ft_strlen(data->input) + 1));
		if (!varname)
		{
			ft_free_all(data);
			ft_exit_w_error(MALLOC_ERROR);
		}
		ft_strlcpy(varname, data->input + i + 1, ft_endwrd(data->input, i));
		varvalue = getenv_local(data->vars, varname)->val;
		free(varname);
	}
	k = 0;
	while (*(varvalue + k))
		*(data->ex_input + j++) = *(varvalue + k++);
	return (k);
}

/*
 * Norma: demasiadas líneas
 */
void	ft_expand(t_data *data)
{
	int	i;
	int	j;

	data->ex_input = (char *)malloc(sizeof(char) * ft_get_expanded_len(data));
	if (!data->ex_input)
	{
		ft_free_all(data);
		ft_exit_w_error(MALLOC_ERROR);
	}
	i = 0;
	j = 0;
	while (*(data->input + i))
	{
		if (*(data->input + i) == '$' && !ft_inside(data->input, i, '\''))
		{
			j += ft_expand_var(data, i, j);
			i += ft_endwrd(data->input, i);
		}
		else if (*(data->input + i) == '~' && !ft_inquotes(data->input, i))
		{
			j += ft_expand_var(data, i, j);
			i += ft_endwrd(data->input, i);
		}
		else if (ft_isspace(*(data->input + i)) && !ft_inquotes(data->input, i))
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
	if (DEBUG == 1)
		printf("\033[0;92m\n    ----> INPUT EXPANSION OK!\n\033[0;39m");
}
