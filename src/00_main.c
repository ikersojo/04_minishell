/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:22:47 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/19 16:09:11 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	t_data	*data;

	// allocatear memoria
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);

	// capturar input -> dejarlo en main?

	// dar por bueno el input
		//syntax ok?
			//no hay simbolos raros --> revisar que todos los chars son ascii y los especiales nos interesan
			//abro lo mismo que cierro
				// contador de caracter (, ), ", ", ', 
			// no empieza ni acaba en una cosa que no sea un comando
		// if not, syntax error
		//todas las variables existen y estan definidas
		//...

	// anular / modificar señales

	// expandir el input
		// variables a texto completo

	// split del input
		// cada instrucción por separado
		// siempre redirgir el output? y luego si no dice nada pasarlo a STDOUT
		

	// definir estrategia de ejecución

	// ejectutar cada comando

	// liberar memoria




	int		i;
	i = -1;
	while (++i < 5)
	{
		data->input = readline(PROMPT);
		if (!data->input)
			return (EXIT_FAILURE);
		if (ft_strlen(data->input) > 0)
			add_history(data->input);
		printf("captured: %s\n", data->input);
		free (data->input);
	}
	free(data);
	return (EXIT_SUCCESS);
}
