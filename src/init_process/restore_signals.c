/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:12 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/14 16:24:08 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	restore_signals(const t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		sigaction(i, &shell->old_handlers[i], 0);
		i++;
	}
}

