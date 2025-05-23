/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:45:18 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/23 20:42:16 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
What needs to be cleaned up within the readline loop 
that isnt useful elsewhere? 

*/

void	readline_cleanup(t_minishell *shell)
{
	if (!shell)
		return ;
	if (shell->current_line)
	{
		free(shell->current_line);
		shell->current_line = 0;
	}
	if (shell->current_pipeline)
	{
		free(shell->current_pipeline);
		shell->current_pipeline = 0;
	}
	if (shell->extra_lines)
	{
		ft_arrclear((void *)shell->extra_lines, free);
		shell->extra_lines = 0;
	}
}
