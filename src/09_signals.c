/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:26:38 by mvalient          #+#    #+#             */
/*   Updated: 2023/03/05 19:57:52 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern t_data	*g_data;

void	ft_parent_signals(int signum, siginfo_t *info, void *context)
{
	(void) context;
	(void) info;
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0); // esta librería no está en MacOS ARMx64. igual por esto me falla el prompt
		rl_redisplay();
	}
}

void	ft_child_signals(int signum, siginfo_t *info, void *context)
{
	(void) context;
	(void) info;
	if (signum == SIGINT)
		ft_free_all(g_data);
}

void	ft_signal_handler(
		void (*handler)(int signum, siginfo_t *info, void *context))
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		write(1, "Error\n", 6);
}
