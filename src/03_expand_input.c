/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_expand_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:44:09 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/08 19:04:10 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_expand_var(t_data *data, int i, int j)
{
	int		k;
	char	*varname;
	char	*varvalue;

	if (*(data->input + i) == '~')
		varvalue = ft_getenv_local(data->vars, "HOME")->val;
	else
	{
		varname = (char *)malloc(sizeof(char) * (ft_strlen(data->input) + 1));
		if (!varname)
		{
			ft_free_all(data);
			ft_exit_w_error(MALLOC_ERROR);
		}
		ft_strlcpy(varname, data->input + i + 1, ft_endwrd(data->input, i));
		varvalue = ft_getenv_local(data->vars, varname)->val;
		free(varname);
	}
	k = 0;
	while (*(varvalue + k))
		*(data->ex_input + j++) = *(varvalue + k++);
	return (k);
}

static int	ft_is_empty_quotes(char *str, int i)
{
	if (*(str + i + 1))
	{
		if ((*(str + i) == '\"' && *(str + i + 1) == '\"')
			|| (*(str + i) == '\'' && *(str + i + 1) == '\''))
			return (1);
	}
	return (0);
}

static void	ft_init_expand(t_data *data, int *i, int *j)
{
	data->ex_input = (char *)malloc(sizeof(char) * ft_get_expanded_len(data));
	if (!data->ex_input)
	{
		ft_free_all(data);
		ft_exit_w_error(MALLOC_ERROR);
	}
	*i = 0;
	*j = 0;
}

void	ft_expand(t_data *data)
{
	int	i;
	int	j;

	ft_init_expand(data, &i, &j);
	while (*(data->input + i))
	{
		if ((*(data->input + i) == '$' && !ft_inside(data->input, i, '\''))
			|| (*(data->input + i) == '~' && !ft_inquotes(data->input, i)))
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
		else if (ft_is_empty_quotes(data->input, i))
			i += 2;
		else
			*(data->ex_input + j++) = *(data->input + i++);
	}
	*(data->ex_input + j) = '\0';
}
