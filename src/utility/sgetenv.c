/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:55:48 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/26 15:47:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

ssize_t	_sgetanon(char **anon, char *name)
{
	ssize_t	i;
	size_t	len;
	char	*temp;

	if (!anon)
		return (-1);
	i = 0;
	temp = str_vec_join((char *[3]){name, "=", 0});
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

/**
 * @brief get an ENV value from the main environment of the shell
 * 
 * Note that this will only check for non-shell-local variables
 * 
 * @param shell the shell struct
 * @param name the name of the variable 
 * @return char* the line from the environment
 */
char	*s_get_env(t_minishell *shell, char *name)
{
	ssize_t	index;

	index = _sgetanon(shell->environment, name);
	if (index >= 0)
		return (shell->environment[index]);
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
ssize_t	s_get_envid(t_minishell *shell, char *name)
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
char	*s_get_interalenv(t_minishell *shell, char *name)
{
	ssize_t	index;

	index = _sgetanon(shell->local_env, name);
	if (index >= 0)
		return (shell->local_env[index]);
	return ((void *)0);
}

/**
 * @brief get an ENV index in the shell local environment 
 * 
 * @param shell the shell struct
 * @param name the name of the environment variable
 * @return ssize_t the index in the array or -1
 */
ssize_t	s_get_internalenvid(t_minishell *shell, char *name)
{
	return (_sgetanon(shell->local_env, name));
}
