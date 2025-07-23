/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_newline_not_end.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:14:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/22 14:19:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	last_newline_not_end(const char *str)
{
	char	*nlp;
	size_t	end_i;

	nlp = ft_strrchr(str, '\n');
	end_i = ft_strlen(str) - 1;
	if (!nlp || nlp != (str + end_i))
		return (1);
	return (0);
}

