/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_any_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:21:20 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/29 17:22:41 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	_remove_from_unassigned(t_minishell *shell, char *name)
{
	void	*new_env;

	new_env = ft_arrdel_atindex((void *)shell->unassigned_env,
			_sgetidx(shell->unassigned_env, name), free);
	ft_dirtyswap((void *)&shell->unassigned_env, new_env, free);
}

int	set_any_env(t_minishell *shell, char **argv, size_t n)
{
	char	*name;
	size_t	i;

	i = 0;
	while (i < n)
	{
		name = ft_strndup(argv[i], ft_strchr(argv[i], '=') - argv[i]);
		if (name == NULL)
			return (-1);
		if (s_get_envid(shell, name) >= 0
			|| _sgetidx(shell->unassigned_env, name) >= 0)
		{
			if (_sgetidx(shell->unassigned_env, name) >= 0)
				_remove_from_unassigned(shell, name);
			set_n_envp(&shell->environment, argv + i, 1);
		}
		else
			set_n_envp(&shell->local_env, argv + i, 1);
		i++;
		free(name);
	}
	return (0);
}

