/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:44:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/23 20:33:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

void	free_strvec(void *a);
/*

Export should be easy it just means updating the environment
in the shell struct
*/

void	export_no_sep(t_minishell *shell, char *item)
{
	char	*name;
	ssize_t	in;

	name = ft_strdup(item);
	in = sgetenv(shell, name);
	if (in < 0)
		ft_dirtyswap((void *)&shell->environment,
			ft_arradd_back(shell->environment, ft_strjoin(item, "=")),
			free_strvec);
	else
		ft_dirtyswap((void *)&shell->environment[in], ft_strjoin(item, "="),
			free_strvec);
}

void	export_with_sep(t_minishell *shell, char *item, char *sep)
{
	char	*name;
	ssize_t	in;

	name = ft_substr(item, 0, sep - item);
	in = sgetenv(shell, name);
	if (in < 0)
		ft_dirtyswap((void *)&shell->environment,
			ft_arradd_back(shell->environment, ft_strdup(item)),
			free_strvec);
	else
		ft_dirtyswap((void *)&shell->environment[in],
			ft_arradd_back(shell->environment, ft_strdup(item)),
			free_strvec);
}

// check if it exists in local vars and remove it
// TODO: rename sgetslenvid function set for clarity
int	builtin_export(t_minishell *shell, char **argv, char **envp)
{
	char	*sep;
	char	*name;
	ssize_t	in;

	if (!argv[1])
		return (builtin_env(shell, argv, envp));
	sep = ft_strchr(argv[1], "=");
	if (!sep)
		export_no_sep(shell, argv[1]);
	else
		export_with_sep(shell, argv[1], sep);
	in = sgetslenvid(shell, name);
	if (in >= 0)
		ft_dirtyswap((void *)&shell->local_env,
			ft_arrdel_atindex(shell->local_env, in), free_strvec);
	if (name)
		free(name);
	return (0);
}
