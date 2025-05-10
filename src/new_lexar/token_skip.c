/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:53:26 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/10 16:00:05 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	token_skip_whitespace(char *str, size_t i)
{
	size_t	start;

	start = i;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	return (i - start);
}

size_t	skip_token(char *str, size_t i)
{
	size_t	start;

	start = i;
	if (str[i] == '\'' || str[i] == '"')
		i += skip_quoted(str, i);
	else if (ft_strchr("<>&|", str[i]))
		i += skip_potential_double(str, i);
	else if (ft_strchr("();", str[i]))
		i++;
	else if (str[i] == '\n'
	else
		i += skip_word(str, i);
	return (i - start);
}