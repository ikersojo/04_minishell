/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:44:59 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/07 21:54:22 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// DEBUG OR PRODUCTION (1 or 0)
# define DEBUG 1

// INCLUDES
# include "../lib/LIBFT/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <dirent.h>
#include <wait.h>

// MESSAGES
# define PROMPT			"\033[0;92m @ minishell_42 > \033[0;39m"
# define MALLOC_ERROR	"Memory could not be allocated.\n"
# define SYNTAX_ERROR	"Syntax error.\n"
# define VAR_ERROR		"User variable not defined.\n"

// DATA STRUCTS
typedef struct s_cmd
{
	int				index;
	char			*str;
	int				is_exec;
	int				is_infd;
	int				is_outfd;
	int				is_par;
	int				is_pipe;
	int				is_and;
	int				is_or;
	int				is_var;
	int				pipe;
	int				par_lvl;
	int				infd;
	int				outfd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_vars
{
	char			*name;
	char			*val;
	struct s_vars	*next;
}					t_vars;

typedef struct s_data
{
	int		exitflag;
	char	*prompt;
	char	*input;
	char	*ex_input;
	int		last_status;
	t_vars	*vars;
	t_cmd	*cmd;
}			t_data;

// FUNCTIONS:

// 01_init_data
t_data	*ft_init_data(int argc, char **argv, char **envp);
t_vars	*ft_varsnew(char *name, char *val);
t_vars	*ft_varslast(t_vars *vars);
void	ft_varsadd_back(t_vars **vars, t_vars *new);
void	ft_mod_status(t_data *data, int status);
char	*ft_gen_prompt(t_data *data);

// 02_check_input
int		ft_input_ok(t_data *data);

// 03_expand_input
void	ft_expand(t_data *data);

// 04_parse_cmds
void	ft_parse(t_data *data);

//06_exec_cmds / heredoc /run_cmd
void	ft_exec_cmds(t_data *data, char **envp);
void	ft_heredoc(char *eof, int outfd);

//99_aux
int		ft_endsub(char *str, int i, char *charset);
int		ft_endredir(char *str, int i);
void	ft_clear_screen(void);
char	*ft_get_var(t_data *data, char *name);
int		ft_inquotes(char *str, int i);
int		ft_inside(char *str, int i, char c);

//99_aux_vars
t_vars  *getenv_local(t_vars *list, char *name);
int setenv_local(t_vars *list, char *name, char *value);

// 99_degub
void	ft_check_data_init(t_data *data);
void	ft_show_parsed(t_data *data);
int		ft_launch_piped_process(char *str, char **envp);
int		ft_launch_process(char *str, int outfd, char **envp);

// 99_free_data
void	ft_free_all(t_data *data);
void	ft_freecmd(t_data *data);
int		ft_is_var_definition(char *str);

#endif
