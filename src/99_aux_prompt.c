/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:53:58 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/18 10:40:19 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_fill(char **prompt, char *str, int *i)
{
	char	*aux;
	int		j;

	aux = ft_strdup(str);
	j = 0;
	while (*(aux + j))
	{
		*((*prompt) + *i) = *(aux + j++);
		*i = *i + 1;
	}
	if (aux != NULL)
		free (aux);
}

char	*ft_gen_prompt(t_data *data)
{
	char	*prompt;
	char	*str_user;
	char	*str_pwd;
	int		i;

	if ((ft_getenv_local(data->vars, "USER") == NULL)
		|| (ft_getenv_local(data->vars, "PWD") == NULL))
		return (NULL);
	str_user = ft_getenv_local(data->vars, "USER")->val;
	str_pwd = ft_getenv_local(data->vars, "PWD")->val;
	prompt = (char *)malloc(ft_strlen(str_user) + ft_strlen(str_pwd) + 100);
	if (!prompt)
		return (NULL);
	i = 0;
	ft_fill(&prompt, "\033[0;96m", &i);
	ft_fill(&prompt, str_user, &i);
	ft_fill(&prompt, "\033[0;90m @ \033[0;94m", &i);
	ft_fill(&prompt, str_pwd, &i);
	if (ft_strcmp(ft_getenv_local(data->vars, "?")->val, "0") == 0)
		ft_fill(&prompt, " \033[0;92m$ \033[0;39m", &i);
	else
		ft_fill(&prompt, " \033[0;31m$ \033[0;39m", &i);
	*(prompt + i) = '\0';
	return (prompt);
}
