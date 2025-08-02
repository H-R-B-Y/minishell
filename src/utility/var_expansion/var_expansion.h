/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:58:25 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/02 12:14:12 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_EXPANSION_H
# define VAR_EXPANSION_H
# include "../../../include/minishell.h"

typedef struct	s_expansion
{
	char			**out;
	const char		*value;
	size_t			v_i;
	size_t			o_i;
	t_quote_mode	mode;
	int				flag;
}				t_expansion;

typedef ssize_t	(*t_special_var_fnc)(t_minishell *, const char *, char **);

struct s_special_var
{
	const char			*match;
	t_special_var_fnc	f;
};

const struct s_special_var	*get_special(char c);

#endif
