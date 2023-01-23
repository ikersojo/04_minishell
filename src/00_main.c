/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:22:47 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/22 11:16:09 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_init_data(argc, argv, envp);
	//DEBUG: -----------------------
	//check that the content has been correctly extracted:
		// printf("t_vars vars:\n");
		// int	i;
		// i = -1;
		// while (((data->vars + (++i))->val))
		// 	printf("    item %d: %s --> %s\n", i, ((data->vars + i)->name), ((data->vars + i)->val));
		// printf("\n\n");
		// printf("MEMORY INITIALIZED!!\n\n");
	//DEBUG: -----------------------


	while (!data->exitflag)
	{
		data->input = readline(data->prompt);
		if (!data->input)
			return (EXIT_FAILURE);
		if (ft_strlen(data->input) > 0)
			add_history(data->input); //ojo, hay que resetear el prompt si le damos a las flechas: hace algo raro!!!
		//ver si exit o realmente vamos a hacer algo --> si ponemos exit despues de un && tendremos que salir como parte de un comando. ojo con liberar el input de la que salimos!
		if (ft_strcmp("exit", data->input) == 0)
			data->exitflag = 1;
		else if (ft_input_ok(data))
		{

			//hacer cosas... (ver abajo)
			printf("\033[0;92mcaptured good input :) --> \033[0;39m%s\n", data->input); // DEBUG
			
			ft_expand(data);

			printf("\033[0;92mexpanded good input :) --> \033[0;39m%s\n", data->ex_input); // DEBUG

			ft_parse(data);

			t_cmd *temp = data->cmd;
			while (temp)
			{
				printf("cmd %d: %s\n", data->cmd->index, data->cmd->str);
				temp = data->cmd->next;
			}


		}
		free (data->input);
	}
	ft_free_all(data);
	return (EXIT_SUCCESS);
}




// COSAS QUE HACER:

	// expandir el input
		// variables a texto completo

	//------> STRING SOBRE LA QUE TRABAJAR <------------

	//definir struct de ejecutor
	//generar lista y rellenar con los comandos,tal y como salen (redirecciones etc son tmabién comandos)
	// ordenar comandos

	// notas
		// siempre redirgir el output y luego si no dice nada pasarlo a STDOUT
		//input y output en el struct
		

	// ejectutar cada comando