/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_03_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:37:00 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/24 22:56:30 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * For  each  name, remove the corresponding variable or function from the
 * environment.
 *
 * Returns
 * 		0: On Failure
 * 		1: On Success
 */
int	unset_builtin(t_vars *env, char **cmd)
{
	int	i;
	int status;

	if (!ft_strcmp(cmd[0], "unset"))
		return (!printf("RTFM: Undefined error.\n"));
	i = 0;
	status = 0;
	while (cmd[++i])
		status += setenv_local(env, cmd[1], "", 1);
	return (!status);
}




//COMBINAR ESTA FUNCION CON LA DE ARRIBA (la dejo como inspiración)
void	ft_varsdel(t_data *data, char *name) // BORAR UNA VEZ RECICLADO EL CODIGO
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