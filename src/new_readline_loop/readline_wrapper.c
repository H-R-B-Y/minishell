/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_wrapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:22:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/28 14:04:03 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/get_next_line.h"


char	*readline_wrapper(t_readline_data *data, const char *prompt)
{
	char	*p[2];

	ft_memset((void *)p, 0, sizeof(p));
	if (*data->interactive_mode)
		return (readline(prompt));
	p[0] = get_next_line(STDIN_FILENO);
	p[1] = ft_strrchr(p[0], '\n');
	if (p[1])
		*p[1] = '\0';
	return (p[0]);
}
