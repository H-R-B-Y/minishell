/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:45:56 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/23 20:37:43 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*_pop_line(t_minishell *shell)
{
	char	*str;

	str = shell->extra_lines[0];
	ft_memmove(shell->extra_lines, &shell->extra_lines[1],
		(ft_arrlen((void *)&shell->extra_lines[1]) + 1) * sizeof(char *));
	if (ft_arrlen((void *)shell->extra_lines) == 0)
	{
		free(shell->extra_lines);
		shell->extra_lines = 0;
	}
	return (str);
}
