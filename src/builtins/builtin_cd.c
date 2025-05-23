/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:31:30 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/23 20:31:50 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int	builtin_cd(t_minishell *shell, char **argv, char **envp)
{
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = 0;
	if (!argv[1])
	{
		tmp = getenv("HOME");
		tmp = ft_strdup(ft_strchr(tmp, '=') + 1);
		ret = chdir(tmp);
	}
	else
		ret = chdir(argv[1]);
	perror("minishell: cd");
	return (!!ret);
}
