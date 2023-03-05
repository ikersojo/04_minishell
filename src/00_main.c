/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:22:47 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/05 18:28:33 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data *g_data;

static void	ft_process_input()
{
	ft_expand(g_data);
	ft_parse(g_data);
	if (DEBUG == 1)
		ft_show_parsed(g_data);
	ft_setup_redir(g_data);
	if (DEBUG == 1)
		ft_show_parsed(g_data);
	ft_exec_cmds(g_data);
	free (g_data->ex_input);
	g_data->ex_input = NULL;
	ft_freecmd(g_data);
}

static void prompt()
{
	rl_set_prompt(PROMPT);
	g_data->input = readline(PROMPT);
	if (!g_data->input)
		ft_exit_w_error(MALLOC_ERROR);
	if (g_data->input && ft_strlen(g_data->input) > 0)
		add_history(g_data->input);
	if (ft_input_ok(g_data))
		ft_process_input();
	replace_history_entry(history_length, g_data->input, NULL);
	free (g_data->input);
	g_data->input = NULL;
}

int	main(int argc, char **argv, char **envp)
{

	(void)argv;
	if (argc != 1)
		ft_exit_w_error(SYNTAX_ERROR);
	g_data = ft_init_data(envp);
	if (DEBUG == 1)
		ft_show_vars(g_data);
	else
		ft_clear_screen();
	rl_initialize();
	using_history();
	ft_signal_handler(ft_parent_signals);
	while (1)
		prompt();
}

// TODO : (DONE) Si se borra el path del env hay segfault -> Comprobar si existe path antes de hacer execve (Iker)
			// He comprobado el resto de variables, y no pasa el input check si no existe. El único problema era con PATH porque lo llamas directamente sin necesidad de ponerlo en el prompt
// TODO : (DONE) Revisar caso de comillas sin contenido (Iker)
			// limpiado al expandir
// TODO : export y env de bash me printan 2 líneas de más con wc -l (Martin)
// TODO : Revisar leaks (Martin)
// TODO : No sé por qué se printa el input de readline -> revisar al final

// Último update (iker 28-02-2023):
	// fixed merge
	// fixed env builtin --> hay que poner los exportables??? tenemos que evitar el ? al printar?
	// fixed echo builtin --> additional last space removed
	// new function: sequencia limpia revisada que es ejecutable/pipe/ejecutable... --> sino, syntax error
	// new function: puede estar la entrada redirigida en un built in? de momento he puesto como un syntax error
	// pipes with builtins working !!! (por fin...)

// update (iker 26-02-2023):
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
		// status de salida (void --> int en las funciones)
		// hay que incluir las redirecionesde salidas de los built-ins echo y pwd (alguno más) --> con está te ayudo (la dejamos para el final)
	// usar variable global?? para que y por qué?
	// redirecciones (iker):
		// cambiar a multi-rebote con while todas las salidas
		// refactor: es clave darle una vuelta para ganar robustez
