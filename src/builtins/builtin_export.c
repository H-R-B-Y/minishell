/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:44:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/01 23:46:32 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

void	free_strvec(void *a);
/*

Export should be easy it just means updating the environment
in the shell struct
*/

void	export_no_sep(t_minishell *shell, char *item, char *name)
{
	ssize_t	in;

	in = s_get_envid(shell, name);
	if (in < 0)
		ft_dirtyswap((void *)&shell->environment,
			ft_arradd_back((void *)shell->environment, ft_strjoin(item, "=")),
			free);
	else
		ft_dirtyswap((void *)&shell->environment[in], ft_strjoin(item, "="),
			free);
}

void	export_with_sep(t_minishell *shell, char *item, char *name)
{
	ssize_t	in;

	in = s_get_envid(shell, name);
	if (in < 0)
		ft_dirtyswap((void *)&shell->environment,
			ft_arradd_back((void *)shell->environment, ft_strdup(item)),
			free);
	else
		ft_dirtyswap((void *)&shell->environment[in],
			ft_arradd_back((void *)shell->environment, ft_strdup(item)),
			free);
}

// check if it exists in local vars and remove it
// TODO: rename s_get_internalenvid function set for clarity
int	builtin_export(t_minishell *shell, char **argv, char **envp)
{
	char	*sep;
	char	*name;
	ssize_t	in;

	if (!argv[1])
		return (builtin_env(shell, argv, envp));
	sep = ft_strchr(argv[1], '=');
	if (!sep)
		name = ft_strdup(argv[1]);
	else
		name = ft_substr(argv[1], 0, argv[0] - sep);
	(void (*[2])(t_minishell *, char *, char *)){export_no_sep, export_with_sep}
		[!!sep](shell, argv[1], name);
	in = s_get_internalenvid(shell, name);
	if (in >= 0)
		ft_dirtyswap((void *)&shell->local_env,
			ft_arrdel_atindex((void *)shell->local_env, in, free), free);
	if (name)
		free(name);
	return (1);
}
