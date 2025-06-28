/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:44:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/28 19:30:20 by cquinter         ###   ########.fr       */
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
	char 	*dup;
	
	in = _sgetanon(shell->local_env, name);
	if (in >= 0)
		ft_dirtyswap((void *)&shell->environment,
			ft_arradd_back((void *)shell->environment, ft_strdup(shell->local_env[in])),
			free);
	if (_sgetanon(shell->cmd_env, name) >= 0)
	{
		dup = ft_strdup(shell->cmd_env[_sgetanon(shell->cmd_env, name)]);
		if (dup == NULL)
			return ;
		update_env(&shell->environment, dup, name, _sgetanon);
		ft_dirtyswap((void *)&shell->cmd_env, ft_arrdel_atindex((void *)shell->cmd_env,
		 	_sgetanon(shell->cmd_env, name), free), free);
	}
	else if (_sgetanon(shell->environment, name) < 0)
	{
		dup = ft_strdup(item);
		if (dup == NULL)
			return ;
		update_env(&shell->unassigned_env, dup, name, _sgetidx);
	}
}

void	export_with_sep(t_minishell *shell, char *item, char *name)
{
	ssize_t	in;
	char	*dup;
	
	in = _sgetidx(shell->unassigned_env, name);
	if (in >= 0)
		ft_dirtyswap((void *)&shell->unassigned_env, 
			ft_arrdel_atindex((void *)shell->unassigned_env, in, free),
			free);
	if (_sgetanon(shell->cmd_env, name) >= 0)
		ft_dirtyswap((void *)&shell->cmd_env, ft_arrdel_atindex((void *)shell->cmd_env,
		 	_sgetanon(shell->cmd_env, name), free), free);
	dup = ft_strdup(item);
	if (dup == NULL) // Perror??
		return ;
	update_env(&shell->environment, dup, name, _sgetanon);
}

int	export_env_print(t_minishell *shell)
{
	ft_arriter((void *)shell->environment, export_print_and_ret);
	ft_arriter((void *)shell->unassigned_env, export_print_and_ret);
	return (1);
}

// check if it exists in local vars and remove it
// TODO: rename s_get_internalenvid function set for clarity
int	builtin_export(t_minishell *shell, char **argv, char **envp)
{
	char	*sep;
	char	*name;
	ssize_t	in;
	size_t	i;

	(void)envp;
	i = 1;
	if (!argv[i])
		return (export_env_print(shell)); //declare --X
	while (i + shell->current_tree->cmd_i < shell->current_tree->token_count)
	{
		sep = ft_strchr(argv[i], '=');
		if (!sep)
			name = ft_strdup(argv[i]);
		else
			name = ft_strndup(argv[i], sep - argv[i]);
		(void (*[2])(t_minishell *, char *, char *)){export_no_sep, export_with_sep}
			[!!sep](shell, argv[i], name);
		in = s_get_internalenvid(shell, name);
		if (in >= 0)
			ft_dirtyswap((void *)&shell->local_env,
				ft_arrdel_atindex((void *)shell->local_env, in, free), free);
		if (name)
			free(name);
		i++;
	}
	return (1);
}
