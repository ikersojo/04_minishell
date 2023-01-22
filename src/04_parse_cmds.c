/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:07 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/22 11:16:09 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_parse(t_data *data)
{
	int		i;
	int		index;
	t_cmd	*temp;

	index = 0;
	i = 0;
	while (*(data->ex_input + i))
	{
		if (*(data->ex_input + i) = ' ')
			i++;
		else
		{
			temp = (t_cmd *)malloc(sizeof(t_cmd));
			if (!temp)
			{
				ft_free_all(data);
				ft_exit_w_error(MALLOC_ERROR);
			}
			temp->index = index++;
			temp->str = ft_substr(data->ex_input, i, ft_next_space(data->ex_input, i));

		}

		temp = data->cmd->next;
	}
}




	temp = data->cmd;