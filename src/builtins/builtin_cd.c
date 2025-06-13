/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:31:30 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/06 16:50:28 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int	builtin_cd(t_minishell *shell, char **argv, char **envp)
{
	char	*tmp;

	(void)envp;
	tmp = 0;
	if (!argv)
		return (errno = EINVAL, perror("builtin_cd"), -1);
	if (argv[1] && argv[2])
		return (ft_putstr_fd("minishell: builtin_cd: too many arguments\n", 2), 0);
	if (!argv[1])
	{
		tmp = s_get_envany(shell, "HOME");
		tmp = ft_strdup(tmp);
		chdir(tmp);
		free(tmp);
	}
	else
		chdir(argv[1]);
	perror("builtin_cd");
	return (1);
}
