/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:44:59 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/28 16:57:20 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "../lib/LIBFT/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

// MESSAGES
# define PROMPT			"\033[0;92m) minishell_42 > \033[0;39m"
# define MALLOC_ERROR	"Memory could not be allocated.\n"
# define SYNTAX_ERROR	"Syntax error.\n"
# define VAR_ERROR		"User variable not defined.\n"

// DATA STRUCTS
typedef struct s_cmd
{
	int				index;
	char			*str;
	int				is_infd;
	int				is_outfd;
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

// 04_parse_cmds.c
void	ft_parse(t_data *data);
void	ft_freecmd(t_data *data);

//05_exec_cmds.c
void	ft_exec_cmds(t_data *data, char **envp);
void	ft_heredoc(char *eof, int outfd);

//99_aux_1.c
int		ft_var_pos(t_data *data, char *varname);
int		ft_endsub(char *str, int i, char *charset);
int		ft_endredir(char *str, int i);
void	ft_clear_screen(void);

#endif
