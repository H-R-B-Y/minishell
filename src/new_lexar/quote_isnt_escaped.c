/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_isnt_escaped.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:18:10 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/13 11:36:35 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	quote_closed(char *str, size_t i, char quote)
{
	if (!str)
		return (0);
	if (str[i] != quote)
		return (0);
	if (str[i] == quote && quote == '\'')
		return (1);
	if (str[i] == quote && quote == '"')
	{
		return (1);
	}
	return (0);
}
