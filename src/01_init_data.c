/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:43:22 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/22 10:09:50 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_all(t_data *data) // estoy liberando algo de más... revisar
{
	int	i;

	if (data->input != NULL)
		free (data->input);
	if (data->ex_input != NULL)
		free (data->ex_input);
	if (data->user != NULL)
		free (data->user);
	if (data->prompt != NULL)
		free (data->prompt);
	if (data->vars != NULL)
	{
		i = 0;
		while ((data->vars + i)->name)
		{
			free((data->vars + i)->name);
			free((data->vars + i++)->val);
		}
		free(data->vars);
	}
	free (data);
}

static void	ft_alloc_vars(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (*(envp + i))
		i++;
	data->vars = (t_vars *)malloc(sizeof(t_vars) * (i)); // ver is hay que implementar el añadir nuevas variables, y si es que si, tendremos que dejar hueco
	if (!data->vars)
	{
		free (data);
		ft_exit_w_error(SYNTAX_ERROR);
	}
}

static void	ft_import_envp(t_data *data, char **envp)
{
	int		i;
	int		loc;
	char	*s;

	ft_alloc_vars(data, envp);
	i = -1;
	while (*(envp + (++i)))
	{
		s = *(envp + i);
		loc = ft_strfind(s, '=');
		if (loc != -1 && loc != 0)
		{
			(data->vars + i)->name = ft_substr(s, 0, loc);
			//poner ifs apra modificar cosas: ejemplo, en la variable shell poner minishell_42...
			(data->vars + i)->val = ft_substr(s, loc + 1, ft_strlen(s) - loc);
			if (ft_strcmp("USER", (data->vars + i)->name) == 0)
				data->user = ft_strjoin("\033[0;92m(", (data->vars + i)->val);
		}
		if (!(data->vars + i)->name || !((data->vars + i)->val))
		{
			ft_free_all(data);
			ft_exit_w_error(MALLOC_ERROR);
		}
	}
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
	ft_import_envp(data, envp); // he pensado en importarlas por si tenemos que añadir más despues
	data->prompt = ft_strjoin(data->user, PROMPT);
	// anular / modificar señales
	return (data);
}
