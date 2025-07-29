/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:31:30 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/29 18:17:13 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

static void _set_pwd_env(t_minishell *shell, char **pwd)
{
	ssize_t	idx;
	char	*dup;

	if (!ft_strchr(pwd[1], '='))
	{
		idx =_sgetanon(shell->environment, "OLDPWD");
		builtin_unset(shell, pwd, NULL);
		if (idx >= 0)
		{
			dup = ft_strdup(pwd[1]);
			if (!dup)
				_free_arr_perror_exit(shell, (void **)pwd, "minishell: cd:");
			update_env(&shell->unassigned_env, dup, "OLDPWD", _sgetidx);
		}
		set_any_env(shell, pwd + 2, 1);
	}
	else
		set_any_env(shell, pwd + 1, 2);
}

static void update_pwd(t_minishell *shell, char **envp)
{
	char	**pwd;
	
	pwd = (char **)ft_calloc(4, sizeof(char *));
	pwd[0] = getcwd(0, 0);
	if (!pwd[0])
		perror_exit(shell, "minishell: cd");
	if (s_get_fromthis_env(envp, "PWD"))
		pwd[1] = str_vec_join((char *[3]){"OLDPWD=", s_get_fromthis_env(envp, "PWD"), 0});
	else if (s_get_envany(shell, "PWD"))
		pwd[1] = str_vec_join((char *[3]){"OLDPWD=", s_get_envany(shell, "PWD"), 0});
	else
		pwd[1] = ft_strdup("OLDPWD");
	if (!pwd[1])
		_free_arr_perror_exit(shell, (void **)pwd, "minishell: cd:");
	pwd[2] = str_vec_join((char *[3]){"PWD=", pwd[0], 0});
	if (!pwd[2])
		_free_arr_perror_exit(shell, (void **)pwd, "minishell: cd:");
	_set_pwd_env(shell, pwd);
	ft_arrclear((void **)pwd, free);
}

int	builtin_cd(t_minishell *shell, char **argv, char ***envp)
{
	char	*tmp;

	(void)envp;
	tmp = 0;
	if (!argv)
		return (errno = EINVAL, perror("builtin_cd"), 1);
	if (argv[1] && argv[2])
		return (ft_putstr_fd("minishell: builtin_cd: too many arguments\n", 2), 1);
	if (!argv[1])
	{
		tmp = s_get_envany(shell, "HOME");
		tmp = ft_strdup(tmp);
		if (!tmp)
			return (perror("minishell: builtin_cd"), 1);
		chdir(tmp);
		free(tmp);
	}
	else
	{
		if (chdir(argv[1]) == -1)
			return (perror("minishell: builtin_cd"), 1);
	}
	update_pwd(shell, *envp);
	return (0);
}
