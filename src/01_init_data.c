/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:43:22 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/28 11:06:42 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_all(t_data *data) // estoy liberando algo de más... revisar
{
	int	i;

	if (data->input != NULL)
	{
		// printf("    FREEALL freeing data->input (%p)\n", data->input); // DEBUG
		free (data->input);
	}
	if (data->ex_input != NULL)
	{
		// printf("    FREEALL freeing data->ex_input (%p)\n", data->ex_input); // DEBUG
		free (data->ex_input);
	}
	if (data->user != NULL)
	{
		// printf("    FREEALL freeing data->user (%p)\n", data->user); // DEBUG
		free (data->user);
	}

	if (data->prompt != NULL)
	{
		// printf("    FREEALL freeing data->prompt (%p)\n", data->prompt); // DEBUG
		free (data->prompt);
	}

	if (data->vars != NULL)
	{
		// printf("    FREEALL data->vars is in (%p)\n", data->vars); // DEBUG
		i = 0;
		while ((data->vars + i)->name)
		{
			// printf("    FREEALL freeing (data->vars + %d)->name (%p)\n", i, (data->vars + i)->name); // DEBUG
			free((data->vars + i)->name);
			// printf("    FREEALL freeing (data->vars + %d)->val (%p)\n", i, (data->vars + i)->val); // DEBUG
			free((data->vars + i++)->val);
		}
		free((data->vars + i)->name);
		free((data->vars + i)->val);
		// printf("    FREEALL freeing data->vars (%p)\n", data->vars); // DEBUG
		free(data->vars);
	}

	if (data->cmd != NULL)
		ft_freecmd(data);
	
	// printf("    FREEALL freeing data (%p)\n", data); // DEBUG
	free (data);
}

static void	ft_alloc_vars(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (*(envp + i))
		i++;
	data->vars = (t_vars *)malloc(sizeof(t_vars) * (i + 1)); // ver is hay que implementar el añadir nuevas variables, y si es que si, tendremos que dejar hueco
	if (!data->vars)
	{
		free (data);
		ft_exit_w_error(SYNTAX_ERROR);
	}
	(data->vars + i + 1)->name = NULL;
	(data->vars + i + 1)->val = NULL;
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
	ft_import_envp(data, envp);
	data->prompt = ft_strjoin(data->user, PROMPT);
	// anular / modificar señales
	return (data);
}
