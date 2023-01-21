/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_expand_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:44:09 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/21 23:27:53 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


// static int	ft_var_exist(char *str, t_data *data)
// {
// 	int		i;
// 	char	*varname;
// 	int		not_found;

// 	not_found = 0;
// 	i = 0;
// 	while (*(str + i))
// 	{
// 		if (*(str + i) == '$')
// 		{
// 			varname = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
// 			if (!varname)
// 				return (0);
// 			ft_strlcpy(varname, str + i + 1, ft_next_space(str, i));
// 			if (ft_var_pos(data, varname) == -1)
// 				not_found = 1;
// 			free(varname);
// 			if (not_found)
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

int	ft_get_expanded_len(t_data *data)
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

static int	ft_expand_var(int count, t_data *data, int i, int j)
{
	//
}

void	ft_expand(t_data *data)
{
	int 	i;
	int		j;
	int		count;

	data->ex_input = (char *)malloc(sizeof(char) * ft_get_expanded_len(data));
	if (!data->ex_input)
	{
		ft_free_all(data);
		ft_exit_w_error(MALLOC_ERROR);
	}
	i = 0;
	while(*(data->input + i))
	{
		if (*(data->input + i) == '$')
		{
			i += ft_next_space(data->input, i);
			j += ft_expand_var(count, data, i, j);
		}
		else
			*(data->ex_input + j++) = *(data->input + i++);
	}
}