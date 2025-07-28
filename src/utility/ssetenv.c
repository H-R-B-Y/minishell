/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssetenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:23:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/28 16:37:01 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

ssize_t	s_get_envid(t_minishell *shell, const char *name);

/*
Note that here we are duping the string
this is because we want to keep our environment variables
de-ailiased so that they are not free'd as part of any cleanup job
the only reason the environment variables should be cleared is
if we are closing the program.

the environment variable array in the shell is
an allocated array of allocated strings.
*/
int	ssetenv(t_minishell *shell, const char *str)
{
	char	*kv[2];
	char	*split;
	ssize_t	index;

	if (!str)
		return (0);
	split = ft_strchr(str, '\n');
	kv[0] = ft_substr(str, 0, split - str);
	kv[1] = ft_strdup(split + 1);
	index = s_get_envid(shell, kv[0]);
	if (!index)
		ft_arradd_back((void *)&shell->environment, ft_strdup(str));
	else
	{
		free(shell->environment[index]);
		shell->environment[index] = ft_strdup(str);
	}
	return (1);
}
