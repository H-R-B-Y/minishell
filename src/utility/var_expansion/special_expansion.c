/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:05:31 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/14 00:33:55 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./var_expansion.h"
#include "../../../include/minishell.h"

const struct s_special_var	*get_special(char c)
{
	int									i;
	static const struct s_special_var	cases[7] = {
		(struct s_special_var){.match = "\"", .f = special_translation},
		(struct s_special_var){.match = "\'", .f = special_ansi_c_quotation},
		(struct s_special_var){.match = "_", .f = special_last_param},
		(struct s_special_var){.match = "?", .f = special_result},
		(struct s_special_var){.match = "$", .f = special_pid},
		(struct s_special_var){.match = "0123456789", .f = special_argv},
		(struct s_special_var){.match = 0, .f = 0}
	};

	i = 0;
	if (!c)
		return (0);
	while (cases[i].match)
	{
		if (ft_strchr(cases[i].match, c))
			return (&cases[i]);
		i++;
	}
	return (0);
}
