/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:45:39 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/16 22:23:15 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_filename(char *str)
{
	int	i;

	i = 0;
	while (ft_ischarset(*(str + i),"<>") || ft_isspace(*(str + i)))
		i++;
	return (str + i);
}

static void	ft_redir_in(t_cmd *temp)
{
	if (*(temp->str + 1) == '<')
	{
		ft_heredoc(ft_filename(temp->str), temp->outfd);
		if(temp->outfd == STDOUT_FILENO)
			temp->next->infd = open(".tempfd", O_RDONLY);
	}
	else
		temp->next->infd = open(ft_filename(temp->str), O_RDONLY);
	if (temp->next->infd == -1)
		ft_exit_w_error("errno");
	dup2(temp->next->infd, STDIN_FILENO);
	close(temp->next->infd);
}

static void	ft_redir_out(t_cmd *temp)
{
	if (*(temp->next->str + 1) == '>')
		temp->outfd = open(ft_filename(temp->next->str),
			O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		temp->outfd = open(ft_filename(temp->next->str),
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (temp->outfd == -1)
		ft_exit_w_error("errno");
}

static void	ft_setup_redir(t_data *data)
{
	t_cmd	*temp;

	temp = data->cmd;
	while (temp)
	{
		if (temp->next && temp->next->is_outfd == 1)
			ft_redir_out(temp);
		if (temp->is_infd && temp->next)
			ft_redir_in(temp);
		temp = temp->next;
	}
}

static int	ft_addvar(t_data *data, char *s)
{
	t_vars	*tmp;
	int		loc;
	char	*name;
	char	*name_tr;
	char	*val;

	loc = ft_strfind(s, '=');
	name = ft_substr(s, 0, loc);
	name_tr = ft_strtrim(name, " \t");
	free (name);
	val = ft_substr(s, loc + 1, ft_strlen(s) - loc);
	tmp = data->vars;
	while (tmp)
	{
		if (ft_strcmp(name_tr, tmp->name) == 0)
		{
			tmp->val = ft_strtrim(val, " \t");
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		tmp = ft_varsnew(name_tr, ft_strtrim(val, " \t"));
		ft_varsadd_back(&data->vars, tmp);
	}
	free (val);
	return (0);
}

void	ft_exec_cmds(t_data *data, char **envp)
{
	t_cmd	*temp;
	pid_t	pid;
	int		status;

	temp = data->cmd;
	while (temp)
	{
		if (temp->is_var == 1)
			status =ft_addvar(data, temp->str);
		temp = temp->next;
	}
	pid = fork();
	if (pid == -1)
		ft_exit_w_error("errno");
	if (pid > 0)
	{
		waitpid(pid, &data->last_status, 0);
		ft_mod_status(data, data->last_status);
		// printf("\033[0;93m    child process for execution completed (exit: %d)\033[0;39m\n", data->last_status); // DEBUG
	}
	else
	{
		ft_setup_redir(data);
		temp = data->cmd;
		while (temp)
		{
			// if (temp->is_ifbuiltin)...
			if (temp->is_exec == 1)
			{
				if (temp->next && temp->next->is_pipe)
					status = ft_launch_piped_process(temp->str, data, envp);
				else
					status = ft_launch_process(temp->str, temp->outfd, data, envp);
			}
			temp = temp->next;
		}
		// printf("\033[0;93m    exec loop completed\033[0;39m\n"); // DEBUG
		ft_free_all(data);
		exit(status);
	}
}
