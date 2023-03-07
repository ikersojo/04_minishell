/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:26:23 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/07 11:27:23 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_filename(char *str)
{
	int	i;

	i = 0;
	while (ft_ischarset(*(str + i), "<>") || ft_isspace(*(str + i)))
		i++;
	return (str + i);
}

void	ft_cmd_clean(t_data *data)
{
	t_cmd	*tmp;
	t_cmd	*current;

	while (data->cmd && (data->cmd->is_infd || data->cmd->is_outfd))
	{
		current = data->cmd;
		data->cmd = data->cmd->next;
		free(current);
	}
	tmp = data->cmd;
	while (tmp)
	{
		while (tmp->next && (tmp->next->is_infd || tmp->next->is_outfd))
		{
			current = tmp->next;
			tmp->next = tmp->next->next;
			free(current);
		}
		tmp = tmp->next;
	}
}
