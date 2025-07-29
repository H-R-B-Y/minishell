/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgetenvany.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:06:15 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/28 15:57:01 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *s_get_envany(t_minishell *shell, char *name)
{
	ssize_t	i;

	i = s_get_envid(shell, name);
	if (i >= 0)
		return (shell->environment[i] + ft_strlen(name) + 1);
	i = s_get_internalenvid(shell, name);
	if (i >= 0)
		return (shell->local_env[i] + ft_strlen(name) + 1);
	return (NULL);
}
