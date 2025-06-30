/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:13:24 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/30 20:04:52 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"


void	unset_any(t_minishell *shell, char *name)
{
	ssize_t	in;
	
	in = s_get_envid(shell, name);
	if (in >= 0)
		ft_dirtyswap((void *)&shell->environment,
			ft_arrdel_atindex((void *)shell->environment, in, free),
			free);
	in = s_get_internalenvid(shell, name);
	if (in >= 0)
		ft_dirtyswap((void *)&shell->local_env,
			ft_arrdel_atindex((void *)shell->local_env, in, free), free);
	in = _sgetidx(shell->unassigned_env, name);
	if (in >= 0)
		ft_dirtyswap((void *)&shell->unassigned_env,
			ft_arrdel_atindex((void *)shell->unassigned_env, in, free), free);
}

int	builtin_unset(t_minishell *shell, char **argv, char ***envp)
{
	char	*name;
	size_t	i;

	(void)envp;
	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '=') && i++)
			continue ;
		name = ft_strdup(argv[i++]);
		if (!name)
			return (perror("minishell: unset"), 1);
		unset_any(shell, name);
		free(name);
	}
	return (0);
}
