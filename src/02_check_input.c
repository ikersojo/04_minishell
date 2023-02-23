/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:42:50 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/23 23:32:00 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_valid_char(char c)
{
	if (ft_isalnum(c) || ft_ischarset(c, " \t\'\"|<>$-_.+~/"))
		return (1);
	return (0);
}

static int	ft_characters_ok(char *str)
{
	int		i;

	i = 0;
	while (*(str + i))
	{
		if (!ft_inquotes(str, i) && !ft_valid_char(*(str + i)))
			{
			printf("error %c \n", *(str + i));
			return (0);
			}
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

static int	ft_quotes_ok(char *str)
{
	int single_quote = 0;
	int double_quote = 0;

	while (*str != '\0')
	{
		if (*str == '\'')
		{
			if (!double_quote)
				single_quote = !single_quote;
		}
		else if (*str == '\"')
		{
			if (!single_quote)
				double_quote = !double_quote;
		}
		str++;
	}
	if (single_quote == 0 && double_quote == 0)
		return (1);
	return (0);
}

static int	ft_var_exist(char *str, t_data *data)
{
	int		i;
	char	*varname;
	int		not_found;

	not_found = 0;
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '$')
		{
			varname = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
			if (!varname)
			{
				ft_free_all(data);
				ft_exit_w_error(MALLOC_ERROR);
			}
			ft_strlcpy(varname, str + i + 1, ft_endwrd(str, i));
			if(!getenv_local(data->vars, varname))
				not_found = 1;
			free(varname);
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
	if (!ft_quotes_ok(str) || !ft_characters_ok(str)
		|| ft_ischarset(*str, "|")
		|| ft_ischarset(*(str + ft_strlen(str) - 1), "|><"))
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
	if (DEBUG == 1)
		printf("\033[0;92m\n    ----> INPUT OK!\n\033[0;39m");
	return (1);
}
