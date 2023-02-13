/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalient <mvalient@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:52:54 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/11 16:14:58 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * The getenv_local function   searches the environment  list to find the
 * envi‐ronment variable name, and returns a pointer to the corresponding
 * element.
 */
t_vars	*getenv_local(t_vars *list, char *name)
{
	while (list)
	{
		if (!ft_strcmp(list->name, name))
		{
			return (list);
		}
		list = list->next;
	}
	return (NULL);
}

/*
 * The setenv_local function adds the variable name to the environment with
 * the value value, if name does  not already exist.  If name does exist in
 * the  environment,  then  its  value is changed  to value if overwrite is
 * nonzero; if overwrite is zero,  then the value of name  is  not  changed
 * and returns a success status.
 */
int	setenv_local(t_vars *list, char *name, char *value, int overwrite)
{
	t_vars	*new;

	new = getenv_local(list, name);
	if (!new)
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
	else if (overwrite)
	{
		free(new->val);
		new->val = ft_strdup(value);
		return (0);
	}
	return (1);
}
