/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:22:47 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/06 23:23:11 by isojo-go         ###   ########.fr       */
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
		ft_check_data_init(data);
	// ft_clear_screen(); // commented for easier debug. remove for production!
	while (!data->exitflag)
	{
		data->input = readline(data->prompt);
		if (!data->input)
			return (EXIT_FAILURE);
		if (ft_strlen(data->input) > 0)
			add_history(data->input);
			//ojo, hay que resetear el prompt si le damos a las flechas: hace algo raro!!!
		if (ft_strcmp("exit", data->input) == 0)
			data->exitflag = 1;
		else if (ft_input_ok(data))
			ft_process_input(data, envp);
		free (data->input);
		data->input = NULL;
	}
	ft_free_all(data);
	return (EXIT_SUCCESS);
}




// COSAS PENDIENTES POR HACER:
	// ordenar comandos y usar paraentesis --> ahora mismo ejecuta en orden
	// incluir || en lógica de ejecución
	// wildcards * deben funcionar para el directorio actua
	// built-ins
	// redirigir señales (usar variable global??)

