/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:22:47 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/19 23:17:17 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_init_data(argc, argv, envp);
	//DEBUG: -----------------------
		//check that the content has been correctly extracted:
		printf("t_vars vars:\n");
		int	i;
		i = -1;
		while (((data->vars + (++i))->val))
			printf("    item %d: %s --> %s\n", i, ((data->vars + i)->name), ((data->vars + i)->val));
		printf("\n\n");
		printf("MEMORY INITIALIZED!!\n\n");
	//DEBUG: -----------------------


	while (!data->exitflag)
	{
		// capturar input -> dejarlo en main?
		data->input = readline(PROMPT);
		if (!data->input)
			return (EXIT_FAILURE);

		//si no está vacio, añadirlo a history
		if (ft_strlen(data->input) > 0)
			add_history(data->input);

		//ver si exit o realmente vamos a hacer algo --> si ponemos exit despues de un && tendremos que salir como parte de un comando. ojo con liberar el input de la que salimos!
		if (ft_strcmp("exit", data->input) == 0)
			data->exitflag = 1;
		else
		{
			//hacer cosas... (ver abajo)
			printf("captured: %s\n", data->input);


		}
		// liberar memoria
		free (data->input);
	}
	ft_free_all(data);
	return (EXIT_SUCCESS);
}




// COSAS QUE HACER:
	// dar por bueno el input
		//syntax ok?
			//no hay simbolos raros --> revisar que todos los chars son ascii y los especiales nos interesan
			//abro lo mismo que cierro
				// contador de caracter (, ), ", ", ', ...
			// no empieza ni acaba en una cosa que no sea un comando
		// if not, syntax error
		//todas las variables existen y estan definidas
		//...


	// expandir el input
		// variables a texto completo

	//------> STRING SOBRE LA QUE TRABAJAR <------------

	// split del input
		// cada instrucción por separado
		// siempre redirgir el output? y luego si no dice nada pasarlo a STDOUT
		

	// definir estrategia de ejecución

	// ejectutar cada comando