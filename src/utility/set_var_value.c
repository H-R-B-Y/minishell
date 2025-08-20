/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:34:30 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/20 15:56:13 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	_set_var_value(t_minishell *shell,
	const char *value,
	const char *var, char ***envp)
{
	char	*dup;

	dup = str_vec_join((const char *[4]){var, "=", value, 0});
	if (!dup)
		perror_exit(shell, "setting var value");
	else if (update_env(envp, dup, "_", _sgetanon) == -1)
		(free(dup), perror_exit(shell, "setting var value"));
}
