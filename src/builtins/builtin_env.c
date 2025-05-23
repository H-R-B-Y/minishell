/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/23 14:09:17 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

void	*print_and_ret(void *p);

int	builtin_env(t_minishell *shell, char **argv, char **envp)
{
	size_t	i;

	i = 0;
	ft_arriter(envp, print_and_ret);
	ft_arriter(shell->local_env, print_and_ret);
	return (0);
}
