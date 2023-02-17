/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:22:47 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/16 18:41:24 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_process_input(t_data *data, char **envp)
{
	ft_expand(data);
	ft_parse(data);
	if (DEBUG == 1)
		ft_show_parsed(data);
	ft_exec_cmds(data, envp);
	free (data->ex_input);
	data->ex_input = NULL;
	ft_freecmd(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_init_data(argc, argv, envp);
	if (DEBUG == 1)
		ft_show_vars(data);
	else
		ft_clear_screen();
	while (!data->exitflag)
	{
		data->input = readline(PROMPT);
		if (!data->input)
			return (EXIT_FAILURE);
		if (ft_strlen(data->input) > 0)
			add_history(data->input);
		if (ft_strcmp("exit", data->input) == 0)
			data->exitflag = 1; // modificar por built-in
		else if (ft_input_ok(data))
			ft_process_input(data, envp);
		free (data->input);
		data->input = NULL;
	}
	ft_free_all(data);
	return (EXIT_SUCCESS);
}

// COSAS PENDIENTES POR HACER:
	// built-ins
	// redirigir señales (usar variable global??)
	// añadir redir in a despues (tiene prioridad el de la derecha)
	// cambiar a multi-rebote
	// cd para actualizar directorio
		// al actualizar directorio, actualzar prompt
		// si vamos a actualizar el prompt en cada vuelta, podemos cambiar el color en función de si el último comando está ok
		
	
// Errorcillos:
// exit status

// martin: señales y exit
// iker: env, export, echo $