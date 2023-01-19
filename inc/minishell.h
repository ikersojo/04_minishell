/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:44:59 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/19 16:09:19 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "../lib/LIBFT/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

// MESSAGES
# define PROMPT			"minishell > "
# define MALLOC_ERROR	"Memory could not be allocated.\n"
//... ver cuales necesitamos para incluir aquí. el subject permite perror, o sea que muchos no tendremos que codificar

// DATA STRUCTS

typedef struct s_vars
{
	char	*name;
	char	*content;
}			t_vars;

typedef struct s_data
{
	char	*input;
	int		noff_cmds;
	char	**cmds;
	t_vars	*vars;
}			t_data;

// FUNCTIONS:



#endif
