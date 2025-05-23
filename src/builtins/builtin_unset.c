/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:13:24 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/23 20:33:58 by hbreeze          ###   ########.fr       */
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

int	builtin_unset(t_minishell *shell, char **argv, char **envp)
{
	ssize_t	in;
	char	*name;
	char	*sep;

	if (!argv[1])
		return (1);
	sep = ft_strchr(argv[1], '=');
	if (!sep)
		name = ft_strdup(argv[1]);
	else
		name = ft_substr(argv[1], 0, sep - argv[1]);
	if (!name)
		return (1);
	in = sgetenvid(shell, name);
	if (in >= 0)
		ft_dirtyswap(shell->environment,
			ft_arrdel_atindex(shell->environment, in), free_strvec);
	in = sgetslenv(shell, name);
	if (in >= 0)
		ft_dirtyswap(shell->local_env,
			ft_arrdel_atindex(shell->local_env, in), free_strvec);
	return (0);
}
