/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgetenvany.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:06:15 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/27 17:27:16 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *s_get_envany(t_minishell *shell, char *name)
{
	ssize_t	i;

	i = s_get_envid(shell, name);
	if (i >= 0)
		return (shell->environment[i]);
	i = s_get_internalenvid(shell, name);
	if (i >= 0)
		return (shell->local_env[i]);
	return ("");
}
