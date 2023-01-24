/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:44:59 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/24 12:41:06 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "../lib/LIBFT/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

// MESSAGES
# define PROMPT			"\033[0;92m) minishell_42 > \033[0;39m"
# define MALLOC_ERROR	"Memory could not be allocated.\n"
# define SYNTAX_ERROR	"Syntax error.\n"
# define VAR_ERROR		"User variable not defined.\n"
//... ver cuales necesitamos para incluir aquí. el subject permite perror, o sea que muchos no tendremos que codificar

// DATA STRUCTS
typedef struct s_cmd
{
	int				index;
	char			*str;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_vars
{
	char	*name;
	char	*val;
}			t_vars;

typedef struct s_data
{
	int		exitflag;
	char	*user;
	char	*prompt;
	char	*input;
	char	*ex_input;
	t_vars	*vars;
	t_cmd	*cmd;
}			t_data;

// FUNCTIONS:

// 01_init_data.c
t_data	*ft_init_data(int argc, char **argv, char **envp);
void	ft_free_all(t_data *data);

// 02_check_input.c
int		ft_input_ok(t_data *data);
int		ft_inquotes(char *str, int i);

// 03_expand_input.c

void	ft_expand(t_data *data);

void	ft_parse(t_data *data);
void	ft_freecmd(t_data *data);

void	ft_launch_process(char *str, char **envp);

//99_aux_1.c

int		ft_var_pos(t_data *data, char *varname);

#endif
