/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:58:25 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/14 00:40:09 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_EXPANSION_H
# define VAR_EXPANSION_H
# include "../../../include/minishell.h"

typedef struct s_expansion
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

ssize_t						special_ansi_c_quotation(t_minishell *shell,
								const char *value,
								char **output);
ssize_t						special_translation(t_minishell *shell,
								const char *value,
								char **output);
ssize_t						special_last_param(t_minishell *shell,
								const char *value,
								char **output);
ssize_t						special_pid(t_minishell *shell,
								const char *value,
								char **output);
ssize_t						special_result(t_minishell *shell,
								const char *value,
								char **output);
ssize_t						special_argv(t_minishell *shell,
								const char *value,
								char **output);

ssize_t						is_special(t_minishell *shell,
								t_expansion *ex, char **res);
ssize_t						is_normal(t_minishell *shell,
								t_expansion *ex, char **res);

ssize_t						_handle_word_split(t_expansion *ex, char **res);

#endif
