/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_aux_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:18:26 by isojo-go          #+#    #+#             */
/*   Updated: 2023/03/08 19:52:04 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_clear_screen(void)
{
	ft_putstr_fd("\n\n\n\n", 1);
	ft_putstr_fd(GREEN, 1);
	ft_putstr_fd("                                                     \n", 1);
	ft_putstr_fd("           :::      ::::::::                         \n", 1);
	ft_putstr_fd("         :+:      :+:    :+:                         \n", 1);
	ft_putstr_fd("       +:+ +:+         +:+                           \n", 1);
	ft_putstr_fd("     +#+  +:+       +#+        \t\tminishell 42 by:  \n", 1);
	ft_putstr_fd("   +#+#+#+#+#+   +#+           \t\tmvalient          \n", 1);
	ft_putstr_fd("        #+#    #+#             \t\tisojo-go          \n", 1);
	ft_putstr_fd("       ###   ########.fr                             \n", 1);
	ft_putstr_fd("                                                     \n", 1);
	ft_putstr_fd(DEF_COLOR, 1);
}

int	ft_starts_with(const char *str, const char *start)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (start[len])
	{
		if (start[len] != str[len])
			return (0);
		len++;
	}
	return (1);
}

int	ft_get_expanded_len(t_data *data)
{
	int		len;
	int		n;
	t_vars	*temp;

	len = 0;
	temp = data->vars;
	while (temp)
	{
		if (ft_strlen(temp->val) > len)
			len = ft_strlen(temp->val);
		temp = temp->next;
	}
	n = ft_count_chars(data->input, '$') + ft_count_chars(data->input, '~');
	return ((len + 1) * n + ft_strlen(data->input) + 1);
}
