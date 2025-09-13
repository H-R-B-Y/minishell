/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:39:57 by cquinter          #+#    #+#             */
/*   Updated: 2025/09/13 14:01:43 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_pwd(t_minishell *shell, char ***envp)
{
	char	**pwd;
	char	*dup;

	pwd = (char **)ft_calloc(3, sizeof(char *));
	pwd[0] = getcwd(0, 0);
	if (!pwd[0])
		perror_exit(shell, "cd");
	pwd[1] = str_vec_join((const char *[3]){"PWD=", pwd[0], 0});
	if (!pwd[1])
	{
		ft_arrclear((void **)pwd, free);
		perror_exit(shell, "cd");
	}
	if (_sgetanon(shell->environment, "OLDPWD") < 0)
	{
		dup = ft_strdup("OLDPWD");
		if (dup == NULL)
			return ;
		update_env(&shell->unassigned_env, dup, "OLDPWD", _sgetidx);
	}
	set_n_envp(envp, pwd + 1, 1);
	ft_arrclear((void **)pwd, free);
}

void	init_shellevel(t_minishell *shell, char ***envp)
{
	char	**pwd;
	int		shelllevel;

	pwd = (char **)ft_calloc(3, sizeof(char *));
	shelllevel = ft_atoi(getenv("SHLVL")) + 1;
	if (shelllevel >= 999 || shelllevel < 0)
	{
		if (shelllevel >= 999)
			ft_fprintf(2,
				"minishell: warning: shell level too high, resetting to 1\n");
		shelllevel = 1 - (shelllevel == -2147483648);
	}
	pwd[0] = ft_itoa(shelllevel);
	pwd[1] = str_vec_join((const char *[3]){"SHLVL=", pwd[0], 0});
	if (!pwd[1])
	{
		ft_arrclear((void **)pwd, free);
		perror_exit(shell, "init");
	}
	set_n_envp(envp, pwd + 1, 1);
	ft_arrclear((void **)pwd, free);
}

void	init_xvars(t_minishell *shell, char ***envp)
{
	init_pwd(shell, envp);
	init_shellevel(shell, envp);
}
