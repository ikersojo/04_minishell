/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_02_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:26:53 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/09 22:38:30 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**ft_trim_str(char *str)
{
	char	**str_arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str_arr = malloc(sizeof(char *) * 2);
	str_arr[0] = malloc(sizeof(char) * ft_strlen(str));
	str_arr[1] = malloc(sizeof(char) * ft_strlen(str));
	while (str[i] != '=')
	{
		str_arr[0][i] = str[i];
		i++;
	}
	str_arr[0][i] = '\0';
	i++;
	while (str[i])
	{
		str_arr[1][j] = str[i];
		i++;
		j++;
	}
	str_arr[1][j] = '\0';
	return (str_arr);
}

static int	ft_export_list(t_vars *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, "_") && ft_strcmp(env->name, "?"))
		{
			if (env->val != NULL)
				printf("declare -x %s=\"%s\"\n", env->name, env->val);
			else
				printf("declare -x %s\n", env->name);
		}
		env = env->next;
	}
	return (0);
}

/*
 * The supplied names are marked for automatic export to the environment of
 * subsequently executed commands. If a variable name is followed by =word,
 * the value of the variable is set to word.  Export returns an exit status
 * of 0 unless an  invalid option is encountered, one of the names is not a
 * valid shell variable name.
 *
 */
int	ft_export_builtin(t_vars **env, char **cmd)
{
	int		i;
	char	**variable;

	i = 0;
	if (ft_strcmp(cmd[i++], "export"))
		return (!printf("RTFM: Undefined error.\n"));
	if (!cmd[i])
		ft_export_list(*env);
	while (cmd[i])
	{
		if (!ft_count_chars(cmd[i], '='))
			ft_setenv_local(*env, cmd[i], NULL, 1);
		else if (ft_strlen(cmd[i]) > 1)
		{
			variable = ft_trim_str(cmd[i]);
			ft_setenv_local(*env, variable[0], variable[1], 1);
			free(variable[0]);
			free(variable[1]);
			free(variable);
		}
		else
			printf("export: `%s': not a valid identifier\n", cmd[i]);
		i++;
	}
	return (0);
}
