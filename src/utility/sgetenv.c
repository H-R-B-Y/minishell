/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgetenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:55:48 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/07 17:29:15 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

ssize_t	_sgetidx(char **anon, const char *name);
ssize_t	_sgetanon(char **anon, const char *name);

/**
 * @brief get an ENV value from the main environment of the shell
 * 
 * Note that this will only check for non-shell-local variables
 * 
 * @param shell the shell struct
 * @param name the name of the variable 
 * @return char* the line from the environment
 */
char	*s_get_env(t_minishell *shell, const char *name)
{
	ssize_t	index;

	index = _sgetanon(shell->environment, name);
	if (index >= 0)
		return (shell->environment[index] + ft_strlen(name) + 1);
	return ((void *)0);
}

/**
 * @brief get an ENV index from the main environment of the shell
 * 
 * Note that this will only check for non-shell-local variables
 * 
 * @param shell the shell struct
 * @param name the name of the variable 
 * @return ssize_t the index in the array or -1
 */
ssize_t	s_get_envid(t_minishell *shell, const char *name)
{
	return (_sgetanon(shell->environment, name));
}

/**
 * @brief get an ENV string from the shell's environment
 * 
 * @param shell the shell struct
 * @param name the name of the environment variable
 * @return char* the env string from the environment
 */
char	*s_get_interalenv(t_minishell *shell, const char *name)
{
	ssize_t	index;

	index = _sgetanon(shell->local_env, name);
	if (index >= 0)
		return (shell->local_env[index] + ft_strlen(name) + 1);
	return ((void *)0);
}

/**
 * @brief get an ENV string from the shell's environment
 * 
 * @param shell the shell struct
 * @param name the name of the environment variable
 * @return char* the env string from the environment
 */
char	*s_get_fromthis_env(char **env, const char *name)
{
	ssize_t	index;

	index = _sgetanon(env, name);
	if (index >= 0)
		return (env[index] + ft_strlen(name) + 1);
	return ((void *)0);
}

/**
 * @brief get an ENV index in the shell local environment 
 * 
 * @param shell the shell struct
 * @param name the name of the environment variable
 * @return ssize_t the index in the array or -1
 */
ssize_t	s_get_internalenvid(t_minishell *shell, const char *name)
{
	return (_sgetanon(shell->local_env, name));
}
