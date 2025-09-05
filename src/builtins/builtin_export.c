/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:44:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/24 18:47:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

void	export_no_sep(t_minishell *shell, char *item, char *name, char ***envp)
{
	ssize_t	i;
	char	*dup;

	i = _sgetanon(shell->local_env, name);
	if (i >= 0)
		ft_dirtyswap((void *)&shell->environment,
			ft_arradd_back((void *)shell->environment,
				ft_strdup(shell->local_env[i])), free);
	if (_sgetanon((*envp), name) >= 0)
	{
		dup = ft_strdup((*envp)[_sgetanon((*envp), name)]);
		if (dup == NULL)
			return ;
		update_env(&shell->environment, dup, name, _sgetanon);
		ft_dirtyswap((void *)envp, ft_arrdel_atindex((void *)(*envp),
				_sgetanon((*envp), name), free), free);
	}
	else if (_sgetanon(shell->environment, name) < 0)
	{
		dup = ft_strdup(item);
		if (dup == NULL)
			return ;
		update_env(&shell->unassigned_env, dup, name, _sgetidx);
	}
}

void	exprt_with_sep(t_minishell *shell, char *item, char *name, char ***envp)
{
	ssize_t	in;
	char	*dup;

	in = _sgetidx(shell->unassigned_env, name);
	if (in >= 0)
		ft_dirtyswap((void *)&shell->unassigned_env,
			ft_arrdel_atindex((void *)shell->unassigned_env, in, free),
			free);
	if (_sgetanon((*envp), name) >= 0)
		ft_dirtyswap((void *)envp, ft_arrdel_atindex((void *)(*envp),
				_sgetanon((*envp), name), free), free);
	dup = ft_strdup(item);
	if (dup == NULL)
		perror_exit(shell, "export with sep: ft_strdup");
	update_env(&shell->environment, dup, name, _sgetanon);
}

int	export_env_print(t_minishell *shell)
{
	ft_arriter((void *)shell->environment, export_print_and_ret);
	ft_arriter((void *)shell->unassigned_env, export_print_and_ret);
	return (0);
}

int	builtin_export(t_minishell *shell, char **argv, char ***envp)
{
	char	*sep;
	char	*name;
	size_t	i;

	i = 1;
	if (!argv[i])
		return (export_env_print(shell));
	while (argv[i])
	{
		sep = ft_strchr(argv[i], '=');
		if (!sep)
			name = ft_strdup(argv[i]);
		else
			name = ft_strndup(argv[i], sep - argv[i]);
		(void (*[2])(t_minishell *, char *, char *, char ***)){export_no_sep,
			exprt_with_sep}[!!sep](shell, argv[i++], name, envp);
		if (s_get_internalenvid(shell, name) >= 0)
			ft_dirtyswap((void *)&shell->local_env,
				ft_arrdel_atindex((void *)shell->local_env,
					s_get_internalenvid(shell, name), free), free);
		if (name)
			free(name);
	}
	return (0);
}
