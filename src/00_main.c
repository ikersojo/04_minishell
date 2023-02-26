/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:22:47 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/26 16:18:03 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_process_input(t_data *data)
{
	ft_expand(data);
	ft_parse(data);
	if (DEBUG == 1)
		ft_show_parsed(data);
	ft_setup_redir(data);
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
		ft_exit_w_error(MALLOC_ERROR);
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

	(void)argv;
	if (argc != 1)
		ft_exit_w_error(SYNTAX_ERROR);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_signal_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		write(1, "Error\n", 6);
	data = ft_init_data(envp);
	if (DEBUG == 1)
		ft_show_vars(data);
	else
		ft_clear_screen();
	while (1)
		prompt(data);
}

// Último update (iker 26-02-2023):
	// Refactored 05, 06, 07
	// redirs and pipes working 100% with execs
	// redirs working on built-ins
	// (!!!) pipes not working on built ins

// update (iker 24-02-2023):
	// Refactored 04
	// added exit status to built-ins

// update (iker 23-02-2023):
	// incluidas re-generaciones de stdin y stdout. Casca por otro lado con pipes, pero con redir no te saca
	// refactorizadas 00, 01, 02, 03 y aux. Sustituidas funciones por setenv y getenv, y duplicidades eliminadas
	// todo lo de arriba cumple norma menos ft_expand, por número de líneas (hay que partir)

// COSAS PENDIENTES POR HACER:
	// built-ins (martin):
		// env, export
		// cd: función que corrija el path del directorio quitando puntos y dobles puntos
		// status de salida (void --> int en las funciones)
		// hay que incluir las redirecionesde salidas de los built-ins echo y pwd (alguno más) --> con está te ayudo (la dejamos para el final)
	// usar variable global?? para que y por qué?
	// redirecciones (iker):
		// cambiar a multi-rebote con while todas las salidas
		// refactor: es clave darle una vuelta para ganar robustez
