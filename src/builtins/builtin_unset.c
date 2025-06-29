/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:13:24 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/29 11:46:39 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

// this should be a utility function 
void	free_strvec(void *a);

/*

Unset is not as easy because unset can be used on both the ENV and the
shell local env, which clearly can be an issue

I also dont have functions to remove items from arrays on the fly
so maybe that is what i should be working!
*/

// order in which we check these shouldnt really matter
// because only one should be true at any given time.

int	builtin_unset(t_minishell *shell, char **argv, char ***envp)
{
	ssize_t	in;
	char	*name;
	char	*sep;

	(void)envp;
	if (!argv[1])
		return (0);
	sep = ft_strchr(argv[1], '=');
	if (!sep)
		name = ft_strdup(argv[1]);
	else
		name = ft_substr(argv[1], 0, sep - argv[1]);
	if (!name)
		return (perror("minishell: unset: unable to malloc"), 1);
	in = s_get_envid(shell, name);
	if (in >= 0)
		ft_dirtyswap((void *)&shell->environment,
			ft_arrdel_atindex((void *)shell->environment, in, free),
			free);
	in = s_get_internalenvid(shell, name);
	if (in >= 0)
		ft_dirtyswap((void *)&shell->local_env,
			ft_arrdel_atindex((void *)shell->local_env, in, free), free);
	if (name)
		free(name);
	return (0);
}
