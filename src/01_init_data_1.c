/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_data_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:43:22 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/13 22:37:01 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_import_envp(t_data *data, char **envp)
{
	t_vars	*tmp;
	int		i;
	int		loc;
	char	*s;

	i = -1;
	while (*(envp + (++i)))
	{
		s = *(envp + i);
		loc = ft_strfind(s, '=');
		if (loc != -1 && loc != 0)
		{
			tmp = ft_varsnew(ft_substr(s, 0, loc), ft_substr(s, loc + 1, ft_strlen(s) - loc));
			ft_varsadd_back(&data->vars, tmp);
		}
	}
	tmp = ft_varsnew(ft_strdup("?"), ft_strdup("0"));
	ft_varsadd_back(&data->vars, tmp);
}

t_data	*ft_init_data(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc != 1)
		ft_exit_w_error(SYNTAX_ERROR);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_exit_w_error(MALLOC_ERROR);
	data->exitflag = 0;
	ft_import_envp(data, envp);
	return (data);
}
