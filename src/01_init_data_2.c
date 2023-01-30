/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_data_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:32:37 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/30 22:33:27 by isojo-go         ###   ########.fr       */
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
