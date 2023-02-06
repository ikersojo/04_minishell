/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalient <mvalient@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:50:01 by mvalient          #+#    #+#             */
/*   Updated: 2023/02/06 23:32:42 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

typedef struct s_argument
{
	char				*argument;
	struct s_argument	*next;
}					t_argument;

/* This builtin is ultimately the way that all user-visible commands should
   change the current working directory. */
int	cd_builtin(t_argument *list)
{
	DIR		directory;
	char	*relative;

	if (!list)
	{
		setenv("PWD", getenv("HOME"), 1);
		return (0);
	}
	if (list->argument[0] == '/')
	{
		directory = opendir(list->argument);
		if (directory)
			setenv("PWD", list->argument);
		free(directory);
		return (0);
	}
	relative = ft_strjoin(getenv("PWD"), list->argument);
	directory = opendir(relative);
	if (directory)
		setenv("PWD", relative);
	free(relative);
	free(directory);
	return (0);
}

/* Print the name of the current working directory. */
int	pwd(t_argument *list)
{
	char	*pwd;

	if (list)
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	pwd = getenv("PWD");
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
