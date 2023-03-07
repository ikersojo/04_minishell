/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_setup_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:05:07 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/07 11:27:23 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_redir_in(t_cmd *exec, t_cmd *inredir)
{
	if (*(inredir->str + 1) == '<')
	{
		ft_heredoc(ft_filename(inredir->str));
		if (exec->outfd == STDOUT_FILENO)
			exec->infd = open(".tempfd", O_RDONLY);
	}
	else
	{
		if (DEBUG == 1)
			ft_print_redir("Input", exec, ft_filename(inredir->str));
		exec->infd = open(ft_filename(inredir->str), O_RDONLY);
	}
	if (exec->infd == -1)
		ft_exit_w_error("errno");
}

static void	ft_redir_out(t_cmd *exec, t_cmd *outredir)
{
	if (DEBUG == 1)
		ft_print_redir("Output", exec, ft_filename(outredir->str));
	if (*(outredir->str + 1) == '>')
		exec->outfd = open(ft_filename(outredir->str),
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		exec->outfd = open(ft_filename(outredir->str),
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (exec->outfd == -1)
		ft_exit_w_error("errno");
}

static void	ft_set_to_null(t_cmd **exec, t_cmd **inredir, t_cmd **outredir)
{
	*exec = NULL;
	*inredir = NULL;
	*outredir = NULL;
}

static void	ft_filter(t_cmd **tmp, t_cmd **exec, t_cmd **inre, t_cmd **outre)
{
	if ((*tmp)->is_outfd)
		*outre = *tmp;
	else if ((*tmp)->is_infd)
		*inre = *tmp;
	else if ((*tmp)->is_exec || (*tmp)->is_builtin)
		*exec = *tmp;
	*tmp = (*tmp)->next;
}

void	ft_setup_redir(t_data *data)
{
	t_cmd	*tmp;
	t_cmd	*exec;
	t_cmd	*inredir;
	t_cmd	*outredir;

	tmp = data->cmd;
	while (tmp)
	{
		ft_set_to_null(&exec, &inredir, &outredir);
		while (tmp && !tmp->is_pipe)
			ft_filter(&tmp, &exec, &inredir, &outredir);
		if (exec && outredir)
			ft_redir_out(exec, outredir);
		if (exec && inredir)
			ft_redir_in(exec, inredir);
		if (tmp)
			tmp = tmp->next;
	}
	ft_cmd_clean(data);
}
