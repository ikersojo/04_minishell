/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:22:47 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/17 12:43:29 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	t_data	*data;

	// anular / modificar señales

	// capturar input -> dejarlo en main

	// dar por bueno el input

	// allocatear memoria

	// expandir el input

	// split del input

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
	return (EXIT_SUCCESS);
}
