/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:44:59 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/24 13:51:55 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// DEBUG OR PRODUCTION (1 or 0)
# define DEBUG 1

#define _XOPEN_SOURCE 700

// INCLUDES
# include "../lib/LIBFT/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>

// MESSAGES
# define PROMPT			"\033[0;92m >> $ \033[0;39m"
# define MALLOC_ERROR	"Memory could not be allocated.\n"
# define SYNTAX_ERROR	"\033[0;31mSyntax error.\033[0;39m\n"
# define VAR_ERROR		"User variable not defined.\n"

// DATA STRUCTS
typedef struct s_cmd
{
	int				index;
	char			*str;
	int				is_exec;
	int				is_infd;
	int				is_outfd;
	int				is_pipe;
	int				is_var;
	int				is_builtin;
	int				pipe;
	int				infd;
	int				outfd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_vars
{
	char			*name;
	char			*val;
	struct s_vars	*next;
	int				is_exp;
}					t_vars;

typedef struct s_data
{
	char	*input;
	char	*ex_input;
	int		last_status;
	int		baseline_infd;
	int		baseline_outfd;
	char	**custom_envp;
	t_vars	*vars;
	t_cmd	*cmd;
}			t_data;

// FUNCTIONS:

// 01_init_data
t_data	*ft_init_data(char **envp);

// 02_check_input
int		ft_input_ok(t_data *data);

// 03_expand_input
void	ft_expand(t_data *data);

// 04_parse_cmds
void	ft_parse(t_data *data);

//05_exec_cmds / heredoc /run_cmd
int		ft_run_builtin(char *full_cmd, t_data *data, int (*builtin)(t_vars *, char **));
void	ft_exec_cmds(t_data *data);
void	ft_heredoc(char *eof, int outfd);
int		ft_launch_piped_process(char *str, int infd, int outfd, t_data *data);
int		ft_launch_process(char *str, int infd, int outfd, t_data *data);
char	*ft_get_path(char *cmd, t_data *data);
char	**ft_get_args(char *arg);

// 06_builtins
int		echo_builtin(t_vars *env, char **cmd);
int		cd_builtin(t_vars *env, char **cmd);
int		pwd_builtin(t_vars *env, char **cmd);

//99_aux
void	ft_clear_screen(void);
int		ft_endsub(char *str, int i, char *charset);
int		ft_endredir(char *str, int i);
// char	*ft_get_var(t_data *data, char *name);
int		ft_inquotes(char *str, int i);
int		ft_inside(char *str, int i, char c);
int		ft_starts_with(const char *str, const char *start);

//99_aux_vars
t_vars  *getenv_local(t_vars *list, char *name);
int 	setenv_local(t_vars *list, char *name, char *value, int overwrite);
t_vars	*ft_varsnew(char *name, char *value);
int		ft_vars_size(t_data *data); // ver si la usamos

//99_aux_cmds
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
t_cmd	*ft_cmdnew(char *str, int index);

// 99_degub
void	ft_show_vars(t_data *data);
void	ft_show_parsed(t_data *data);
void	ft_check_cmd(char *cmd_path, char **cmd);

// 99_free_data
void	ft_free_all(t_data *data);
void	ft_freecmd(t_data *data);
int		ft_is_var_definition(char *str);
void	ft_free_custom_envp(t_data *data);

#endif
