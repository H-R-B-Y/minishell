/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:13:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/02 18:29:31 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Not sure if i should be writing the executor now, or if
it would be better to put some structure

Also see here:
https://stackoverflow.com/questions/1158091/defining-a-variable-with-or-without-export

if you do:
$ MYVAR="1234" echo "$MYVAR"
this will print nothing because the var is defined in the command scope
but the variable being expanded is expanded in the shell scope.

if you do:
$ MYVAR="1234"; echo "$MYVAR"
This WILL print 1234 because the assignment is sequentially before the 
command so the variable is defined in the shells scope so the shell 
can expand the variable.


*/

int	execute_ast()
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