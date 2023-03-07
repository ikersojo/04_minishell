/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_run_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:18:31 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/07 18:30:44 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_lst_to_str(t_vars *tmp)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(ft_strlen(tmp->name) + ft_strlen(tmp->val) + 2);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (*(tmp->name + j))
		*(str + i++) = *(tmp->name + j++);
	*(str + i++) = '=';
	j = 0;
	while (*(tmp->val + j))
		*(str + i++) = *(tmp->val + j++);
	*(str + i++) = '\0';
	return (str);
}

char	**ft_gen_envp(t_data *data)
{
	t_vars	*tmp;
	int		i;
	int		len;
	char	**custom_envp;

	len = ft_vars_size(data);
	custom_envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (custom_envp == NULL)
		return (NULL);
	i = 0;
	tmp = data->vars;
	while (tmp)
	{
		if (tmp->is_exp == 1)
			*(custom_envp + i) = ft_lst_to_str(tmp);
		else
			*(custom_envp + i) = NULL;
		i++;
		tmp = tmp ->next;
	}
	*(custom_envp + i) = NULL;
	return (custom_envp);
}

void	ft_run_command(char *arg, t_data *data, char **envp)
{
	char	**cmd;
	char	*cmd_path;
	int		i;
	int		flag;

	flag = 0;
	cmd = ft_get_args(arg);
	if (*(*(cmd + 0)) == '/' || *(*(cmd + 0)) == '.')
	{
		cmd_path = *(cmd + 0);
		flag = 2;
	}
	else
		cmd_path = ft_get_path(*(cmd + 0), data);
	if (cmd_path == NULL)
		flag = 1;
	else if (execve(cmd_path, cmd, envp) == -1)
		flag = 1;
	i = 0;
	while (*(cmd + i))
		free (*(cmd + i++));
	free (cmd);
	if (flag == 2)
		free (cmd_path);
	if (flag == 1)
		ft_exit_w_error("Command not found\n");
}
