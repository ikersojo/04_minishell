/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:42:50 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/21 12:42:35 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// dar por bueno el input
	//syntax ok?
		//no hay simbolos raros --> revisar que todos los chars son ascii y los especiales nos interesan
		//abro lo mismo que cierro
			// contador de caracter (, ), ", ", ', ...
		// no empieza ni acaba en una cosa que no sea un comando
	// if not, syntax error
	//todas las variables existen y estan definidas
	//...

int	ft_inquotes(char *str, int i)
{
	int	j;
	int	singleq;
	int	doubleq;

	singleq = 0;
	doubleq = 0;
	j = 0;
	while (j < i)
	{
		if (*(str + j) == '\'')
			singleq++;
		if (*(str + j) == '\"')
			doubleq++;
		j++;
	}
	if (singleq % 2 != 0 || doubleq % 2 != 0)
		return (1);
	return (0);
}

int	ft_characters_ok(char *str)
{
	int		i;
	char	c;

	if (ft_count_chars(str, '\'') % 2 != 0)
		return (0);
	if (ft_count_chars(str, '\"') % 2 != 0)
		return (0);
	i = 0;
	while (*(str + i))
	{
		c = *(str + i);
		(void)c; //DEBUG
		// if (ft_inquotes(str, i) && (!ft_isprint(c) || c != 9))
		// 	return (0);
		// if (!ft_inquotes(str, i) && (c == 92 || c == 59)) // add other special characters to be considered a syntax error
		// 	return (0);
		i++;
	}
	return (1);
}

static int ft_parenthesis_ok(char *str)
{
	int		i;
	char	c;
	int		open;
	int		close;

	if (ft_count_chars(str, '(') != ft_count_chars(str, ')'))
		return (0);
	open = 0;
	close = 0;
	i = 0;
	while (*(str + i))
	{
		c = *(str + i);
		if (c == '(')
			open ++;
		if (c == ')')
			close ++;
		if (open - close < 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_input_ok(char *str)
{
	if (!ft_parenthesis_ok(str))
		return (0);
	if (*str == 124 || *(str + ft_strlen(str)) == 124)
		return (0);

	if (ft_characters_ok(str) == 0)
		return (0);
	return (1);
}