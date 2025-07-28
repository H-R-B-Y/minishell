/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:31:30 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/28 13:23:10 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

static void update_pwd(t_minishell *shell, char **envp)
{
	char **pwd;
	
	pwd = (char **)ft_calloc(4, sizeof(char *));
	pwd[0] = getcwd(0, 0);
	if (!pwd[0])
		perror_exit(shell, "minishell: cd");
	if (s_get_fromthis_env(envp, "PWD"))
		pwd[1] = str_vec_join((char *[3]){"OLDPWD=", s_get_fromthis_env(envp, "PWD"), 0});
	else
		pwd[1] = str_vec_join((char *[3]){"OLDPWD=", s_get_envany(shell, "PWD"), 0});
	if (!pwd[1])
	{
		ft_arrclear((void **)pwd, free);
		perror_exit(shell, "minishell:cd");
	}
	pwd[2] = str_vec_join((char *[3]){"PWD=", pwd[0], 0});
	if (!pwd[2])
	{
		ft_arrclear((void **)pwd, free);
		perror_exit(shell, "minishell:cd");
	}
	set_any_env(shell, pwd + 1, 2);
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
