/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:13:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/23 20:42:08 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_ast(void)
{
	/* 
	we can do something like this:

	if (node->type == subshell)
		execute_subshell(node);
	else if (node->type == AND || OR)
		execute_logical(node);
	else if (node->type == PIPE)
		execute_pipe(node)
	else if (node->type == SEQ)
		execute_sequence(node);
	else if (node->type == COMMAND)
		execute_command(node);
	*/
}
