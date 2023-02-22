/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:22:47 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/22 09:29:41 by mvalient         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_process_input(t_data *data)
{
	ft_expand(data);
	ft_parse(data);
	if (DEBUG == 1)
		ft_show_parsed(data);
	ft_exec_cmds(data);
	free (data->ex_input);
	data->ex_input = NULL;
	ft_freecmd(data);
}

static void	ft_signal_handler(int signum, siginfo_t *info, void *context)
{
	(void) signum;
	(void) context;
	(void) info;
	printf("SIGINT");
	exit(0);
}

static void prompt(t_data *data)
{
	data->input = readline(PROMPT);
	if (!data->input)
	{
		// TODO : Tratar caso : return (EXIT_FAILURE);
	}
	if (ft_strlen(data->input) > 0)
		add_history(data->input);
	if (ft_input_ok(data))
		ft_process_input(data);
	free (data->input);
	data->input = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction sa;
	t_data	*data;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_signal_handler;

	if (sigaction(SIGINT, &sa, NULL) == -1)
		write(1, "Error\n", 6);

	data = ft_init_data(argc, argv, envp);
	if (DEBUG == 1)
		ft_show_vars(data);
	else
		ft_clear_screen();
	while (1)
		prompt(data);
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

// martin: señales
// iker: env, export