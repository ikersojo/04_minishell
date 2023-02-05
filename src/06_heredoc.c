/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:04:10 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/05 22:37:06 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_get_input(void)
{
	char	c;
	int		bytes;
	char	*line;
	int		i;

	line = (char *)malloc(400);
	bytes = read(0, &c, 1);
	i = 0;
	while (bytes > 0 && c != '\0')
	{
		*(line + i++) = c;
		if (c == '\n')
			break ;
		bytes = read(0, &c, 1);
	}
	*(line + i) = '\0';
	return (line);
}

static void	ft_checkline(char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = ft_get_input();
		if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
		{
			free (line);
			return ;
		}
		ft_putstr_fd(line, fd);
		free (line);
	}
}

void	ft_heredoc(char *eof, int outfd)
{
	int		tempfd;

	if (outfd == 1)
	{
		tempfd = open(".tempfd", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		ft_checkline(eof, tempfd);
		close (tempfd);
	}
	else
		ft_checkline(eof, outfd);
}
