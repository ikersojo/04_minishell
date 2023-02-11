/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalient <mvalient@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:52:54 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/11 15:24:18 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_vars  *getenv_local(t_vars *list, char *name)
{
	while (list)
	{
		if (!ft_strcmp(list->name, name))
		{
			return (list);
		}
		list->next;
	}
	return (NULL);
}

int setenv_local(t_vars *list, char *name, char *value)
{
	t_vars	*new;
	if (!getenv_local(list, name))
	{
		new = malloc(sizeof(t_vars));
		new->name = name;
		new->val = value;
		new->next = NULL;
		while (list->next)
			list = list->next;
		list->next = new;
		return (0);
	}
	return (1);
}