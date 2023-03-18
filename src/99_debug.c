/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:53:58 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/18 10:40:35 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_show_vars(t_data *data)
{
	t_vars	*temp;

	printf("\033[0;93m\n    ----------------\n\n");
	temp = data->vars;
	while (temp)
	{
		printf("%s=%s (export = %d)\n", temp->name, temp->val, temp->is_exp);
		temp = temp->next;
	}
	printf("\n    ----------------\033[0;39m\n\n");
}

void	ft_show_parsed(t_data *data)
{
	t_cmd	*temp;

	printf("\033[0;93m\n    ----------------\n");
	temp = data->cmd;
	while (temp)
	{
		printf("\n    parsed cmd %d: %s\n", temp->index, temp->str);
		printf("    exec %d builtin %d | infd %d (%d) outfd %d (%d) pipe %d\n",
			temp->is_exec, temp->is_builtin, temp->is_infd, temp->infd,
			temp->is_outfd, temp->outfd, temp->is_pipe);
		temp = temp->next;
	}
	printf("\n    ----------------\033[0;39m\n\n");
}

void	ft_check_cmd(char *cmd_path, char **cmd)
{
	int	i;

	i = 0;
	printf("\033[0;93m\n    ----------------\n\n");
	printf("    cmd_path: %s\n\n", cmd_path);
	while (*(cmd + i))
	{
		printf("    arg[%d]: %s\n", i, *(cmd + i));
		i++;
	}
	printf("\n    ----------------\033[0;39m\n\n");
}

void	ft_print_redir(char *str, t_cmd *exec, char *redir)
{
	printf("\033[0;93m\n    ----------------\n");
	printf("    %s in %s redirected to %s\n", str, exec->str, redir);
	printf("    ----------------\033[0;39m\n\n");
}
