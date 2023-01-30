/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:46:36 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/30 23:12:49 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_check_data_init(t_data *data)
{
	t_vars	*temp;
	int		i;

	printf("\033[0;93m\n    ----------------\n\n");
	printf("    env parameters imported to vars list:\n");
	i = 0;
	temp = data->vars;
	while (temp)
	{
		printf("    env %d: %s  -->  %s\n", i++, temp->name, temp->val);
		temp = temp->next;
	}
	printf("\n    ----------------\033[0;39m\n\n");
}

void	ft_show_parsed(t_data *data)
{
	t_cmd *temp;

	printf("\033[0;93m\n    ----------------\n\n");
	temp = data->cmd;
	while (temp)
	{
		printf("    parsed cmd %d: %s\n", temp->index, temp->str);
		temp = temp->next;
	}
	printf("\n    ----------------\033[0;39m\n\n");
}