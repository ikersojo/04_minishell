/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_data_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:32:37 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/16 18:11:42 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_vars	*ft_varsnew(char *name, char *val)
{
	t_vars	*new;

	new = (t_vars *)malloc(sizeof(t_vars));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->val = val;
	new->next = NULL;
	return (new);
}

t_vars	*ft_varslast(t_vars *vars)
{
	if (vars == NULL)
		return (NULL);
	while (vars->next)
		vars = vars->next;
	return (vars);
}

void	ft_varsadd_back(t_vars **vars, t_vars *new)
{
	t_vars	*tmp;

	if (new && vars)
	{
		if (*vars == NULL)
			*vars = new;
		else
		{
			tmp = ft_varslast(*vars);
			tmp->next = new;
		}
	}
}

void	ft_varsdel(t_data *data, char *name)
{
	t_vars	*tmp;
	t_vars	*aux;

	if (ft_strcmp(data->vars->name, name) == 0)
	{
		aux = data->vars;
		data->vars = data->vars->next;
		free(aux->name);
		free(aux->val);
		free(aux);
	}
	tmp = data->vars->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			aux = tmp;
			tmp->next = tmp->next->next;
			free(aux->name);
			free(aux->val);
			free(aux);
		}
		tmp = tmp->next;
	}
}

void	ft_mod_status(t_data *data, int status)
{
	t_vars	*tmp;

	tmp = data->vars;
	while (tmp)
	{
		if (*tmp->name == '?')
			tmp->val = ft_itoa(status);
		tmp = tmp->next;
	}
}
