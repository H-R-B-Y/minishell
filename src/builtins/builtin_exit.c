/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:38:10 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/22 13:44:27 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

static void warning_message(void)
{
	printf("entire process cleanup has not been implemented yet, memory leaks will occur here");
}

/*
Probably not a good idea to allow memory leaks here, but in fairness
bash leaks here so idk.

I will attempt to cleanup here though, just in case.
*/
int	builtin_exit(t_minishell *shell, char **argv, char **envp)
{
	warning_message();
	exit(0); // think it would be good to accept a status code from input here.
}
