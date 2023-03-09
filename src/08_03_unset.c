/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_03_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:37:00 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/09 22:41:10 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * Function deletes a node from the linked list
 *
 * Returns:
 * 		0: If node is deleted
 * 		1: If no node deleted
 */
int	ft_delete_node(t_vars **env, char *name)
{
	t_vars	*temp;
	t_vars	*prev;

	temp = *env;
	if (temp != NULL && !ft_strcmp(temp->name, name))
	{
		*env = temp->next;
		free(temp->name);
		free(temp->val);
		free(temp);
		return (0);
	}
	while (temp != NULL && ft_strcmp(temp->name, name))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (1);
	prev->next = temp->next;
	free(temp->name);
	free(temp->val);
	free(temp);
	return (0);
}

/*
 * For  each  name, remove the corresponding variable or function from the
 * environment.
 *
 * Returns
 * 		1: On Failure
 * 		0: On Success
 */
int	ft_unset_builtin(t_vars **env, char **cmd)
{
	int	i;
	int	status;

	if (ft_strcmp(cmd[0], "unset"))
		return (!printf("RTFM: Undefined error.\n"));
	i = 0;
	status = 0;
	while (cmd[++i])
		status += ft_delete_node(env, cmd[i]);
	return (status);
}
