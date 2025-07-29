/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgetenvany.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:06:15 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/29 17:20:01 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

ssize_t	_sgetidx(char **anon, const char *name)
{
	ssize_t	i;
	size_t	len;

	if (!anon)
		return (-1);
	i = 0;
	len = ft_strlen(name);
	while (1)
	{
		if (!anon[i])
		{
			i = -1;
			break ;
		}
		if (!ft_strncmp(name, anon[i], len))
			break ;
		i++;
	}
	return (i);
}

ssize_t	_sgetanon(char **anon, const char *name)
{
	ssize_t	i;
	size_t	len;
	char	*temp;

	if (!anon)
		return (-1);
	i = 0;
	temp = str_vec_join((char *[3]){(void *)name, "=", 0});
	len = ft_strlen(temp);
	while (1)
	{
		if (!anon[i])
		{
			i = -1;
			break ;
		}
		if (!ft_strncmp(temp, anon[i], len))
			break ;
		i++;
	}
	free(temp);
	return (i);
}

char	*s_get_envany(t_minishell *shell, const char *name)
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
