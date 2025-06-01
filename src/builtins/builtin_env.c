/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/01 23:46:43 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

void	*print_and_ret(void *p);

int	builtin_env(t_minishell *shell, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	(void)shell;
	ft_arriter((void *)envp, print_and_ret);
	// ft_arriter((void *)shell->environment, print_and_ret);
	return (1);
}
