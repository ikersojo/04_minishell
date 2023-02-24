/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_setup_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:05:07 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/24 15:49:47 by isojo-go         ###   ########.fr       */
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

static void	ft_redir_in_next(t_cmd *temp)
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

static void	ft_redir_in_current(t_cmd *temp)
{
	if (*(temp->next->str + 1) == '<')
	{
		ft_heredoc(ft_filename(temp->next->str), temp->outfd);
		if(temp->outfd == STDOUT_FILENO)
			temp->infd = open(".tempfd", O_RDONLY);
	}
	else
		temp->infd = open(ft_filename(temp->next->str), O_RDONLY);
	if (temp->infd == -1)
		ft_exit_w_error("errno");
	dup2(temp->infd, STDIN_FILENO);
	close(temp->infd);
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

void	ft_setup_redir(t_data *data)
{
	t_cmd	*temp;

	temp = data->cmd;
	while (temp)
	{
		if (temp->next && temp->next->is_outfd == 1)
			ft_redir_out(temp);
		// else if (temp->next && temp->next->next && temp->next->is_infd == 1 && temp->next->next->is_outfd == 1)
		// 	ft_redir_out(temp);
		if (temp->next && temp->next->is_infd)
			ft_redir_in_current(temp);
		else if (temp->is_infd && temp->next)
			ft_redir_in_next(temp);
		temp = temp->next;
	}
}