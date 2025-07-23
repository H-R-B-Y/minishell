/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_wrapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:22:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/22 16:25:04 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/get_next_line.h"


char	*readline_wrapper(t_readline_data *data, const char *prompt)
{
	char	*p[2];

	if (*data->interactive_mode)
		return (readline(prompt));
	p[0] = get_next_line(STDIN_FILENO);
	p[1] = ft_strrchr(p[0], '\n');
	if (p[1])
		*p[1] = '\0';
	return (p[0]);
}
