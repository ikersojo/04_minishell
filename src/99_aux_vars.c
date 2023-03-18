/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:53:58 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/18 10:40:32 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_write_val(t_vars *new, char *value)
{
	if (value != NULL)
		free(new->val);
	if (value != NULL)
		new->val = ft_strdup(value);
	return (0);
}

t_vars	*ft_varsnew(char *name, char *value)
{
	t_vars	*new;

	new = (t_vars *)malloc(sizeof(t_vars));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->val = value;
	new->is_exp = 0;
	new->next = NULL;
	return (new);
}

/*
 * The ft_getenv_local  function  searches  the environment list to find the
 * envi‐ronment variable name, and returns a pointer to the corresponding
 * element.
 */
t_vars	*ft_getenv_local(t_vars *list, char *name)
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
 * The ft_setenv_local function adds the variable name to the environment with
 * the value value, if name does  not already exist.  If name does exist in
 * the  environment,  then  its  value is changed  to value if overwrite is
 * nonzero; if overwrite is zero,  then the value of name  is  not  changed
 * and returns a success status.
 */
int	ft_setenv_local(t_vars *list, char *name, char *value, int overwrite)
{
	t_vars	*new;

	if (!list)
		return (-1);
	new = ft_getenv_local(list, name);
	if (!new)
	{
		if (value == NULL)
			new = ft_varsnew(ft_strdup(name), NULL);
		else
			new = ft_varsnew(ft_strdup(name), ft_strdup(value));
		if (!new)
			return (-1);
		while (list->next)
			list = list->next;
		list->next = new;
		list->is_exp = 0;
		return (0);
	}
	else if (overwrite)
		return (ft_write_val(new, value));
	return (1);
}

int	ft_vars_size(t_data *data)
{
	t_vars	*tmp;
	int		i;

	i = 0;
	tmp = data->vars;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
