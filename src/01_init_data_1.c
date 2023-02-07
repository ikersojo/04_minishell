/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_data_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:43:22 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/07 10:21:51 by isojo-go         ###   ########.fr       */
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

static char	*ft_gen_prompt(t_data *data)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = ft_get_var(data, "USER");
	str2 = ft_strjoin("\033[0;92m\n", str1);
	free (str1);
	str1 = ft_strjoin(str2, PROMPT);
	free (str2);
	str2 = ft_get_var(data, "PWD");
	str3 = ft_strjoin(BLUE, str2);
	free (str2);
	str2 = ft_strjoin(str3, " $ \033[0;39m");
	free (str3);
	str3 = ft_strjoin(str1, str2);
	free (str1);
	free (str2);
	return (str3);
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
	data->prompt = ft_gen_prompt(data);
	// anular / modificar señales
	return (data);
}
