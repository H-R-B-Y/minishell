/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:31:30 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/22 13:21:40 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int	builtin_cd(t_minishell *shell, char **argv, char **envp)
{
	char	*tmp;
	int		ret;
	
	ret = 0;
	if (!argv[1])
	{
		tmp = getenv("HOME");
		tmp = ft_strdup(ft_strchr(tmp, '=') + 1);
		if (chdir(tmp))
		{
			perror(tmp);
			ret = 1;
		}
		free(tmp);
	}
	else if (chdir(argv[1]))
	{
		ret = 1;
		perror(argv[1]);
	}
	return (ret);
}
