/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_expand_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:44:09 by isojo-go          #+#    #+#             */
/*   Updated: 2023/01/21 18:26:23 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


// static int	ft_var_exist(char *str, t_data *data)
// {
// 	int		i;
// 	char	*varname;
// 	int		not_found;

// 	not_found = 0;
// 	i = 0;
// 	while (*(str + i))
// 	{
// 		if (*(str + i) == '$')
// 		{
// 			varname = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
// 			if (!varname)
// 				return (0);
// 			ft_strlcpy(varname, str + i + 1, ft_next_space(str, i));
// 			if (ft_var_pos(data, varname) == -1)
// 				not_found = 1;
// 			free(varname);
// 			if (not_found)
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }