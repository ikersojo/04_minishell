/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:01:27 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/05 16:12:18 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_freecmd(t_data *data)
{
	t_cmd	*tmp;
	t_cmd	*current;

	tmp = data->cmd;
	while(tmp)
	{
		current = tmp;
		tmp = tmp->next;
		free (current->str);
		free (current);
	}
	data->cmd = NULL;
}

static void	ft_freevars(t_data *data)
{
	t_vars	*tmp;
	t_vars	*current;

	tmp = data->vars;
	while(tmp)
	{
		current = tmp;
		tmp = tmp->next;
		free (current->name);
		free (current->val);
		free (current);
	}
	data->vars = NULL;
}

void	ft_free_all(t_data *data)
{
	if (data->input != NULL)
		free (data->input);
	if (data->ex_input != NULL)
		free (data->ex_input);
	// if (data->user != NULL)
	// 	free (data->user);
	if (data->prompt != NULL)
		free (data->prompt);
	if (data->vars != NULL)
		ft_freevars(data);
	if (data->cmd != NULL)
		ft_freecmd(data);
	free (data);
}