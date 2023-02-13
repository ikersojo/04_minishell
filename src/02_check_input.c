/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:42:50 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/13 22:42:08 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_characters_ok(char *str)
{
	int		i;

	if (ft_count_chars(str, '\'') % 2 != 0)
		return (0);
	if (ft_count_chars(str, '\"') % 2 != 0)
		return (0);
	i = 0;
	while (*(str + i))
	{
		if (!ft_inquotes(str, i) && ft_ischarset(*(str + i), "\\;,:!()&"))
			return (0);
		if (!ft_inquotes(str, i) && ft_ischarset(*(str + i), "|")
			&& (*(str + i + 1) && ft_ischarset(*(str + i + 1), "|")))
			return (0);
		if (!ft_inquotes(str, i) && ft_ischarset(*(str + i), "<>")
			&& (*(str + i + 1) && ft_ischarset(*(str + i + 1), "<>")
			&& *(str + i) != *(str + i + 1)))
			return (0);
		if (!ft_inquotes(str, i) && ft_ischarset(*(str + i), "<>")
			&& (*(str + i + 1) && ft_ischarset(*(str + i + 1), "<>"))
			&& (*(str + i + 2) && ft_ischarset(*(str + i + 2), "<>")))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_parenthesis_ok(char *str)
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

static int	ft_var_exist(char *str, t_data *data)
{
	int		i;
	char	*varname;
	int		not_found;
	char	*varvalue;

	not_found = 0;
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '$')
		{
			varname = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
			if (!varname)
				return (0);
			ft_strlcpy(varname, str + i + 1, ft_endwrd(str, i));
			varvalue = ft_get_var(data, varname);
			if (ft_strcmp(varvalue, "unknown") == 0)
				not_found = 1;
			free(varname);
			free(varvalue);
			if (not_found)
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_input_ok(t_data *data)
{
	char	*str;
	int		errorflag;

	errorflag = 0;
	str = ft_strtrim(data->input, " \t");
	if (!ft_parenthesis_ok(str) || !ft_characters_ok(str)
		|| ft_ischarset(*str, "|>")
		|| ft_ischarset(*(str + ft_strlen(str)), "|>"))
	{
		printf(SYNTAX_ERROR);
		errorflag = 1;
	}
	if (!ft_var_exist(str, data))
	{
		printf(VAR_ERROR);
		errorflag = 1;
	}
	free (str);
	if (errorflag == 1)
		return (0);
	return (1);
}
