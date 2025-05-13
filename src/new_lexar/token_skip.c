/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:53:26 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/13 11:30:36 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	skip_quoted(char *str, size_t i, char quote);
size_t	skip_potential_double(char *str, size_t i);
size_t	skip_word(t_tokeniserinternal *meta, char *str, size_t i, char quote);

size_t	token_skip_whitespace(char *str, size_t i)
{
	size_t	start;

	start = 0;
	start = i;
	while (str[i] && ft_iswhitespace(str[i]) && str[i] != '\n')
		i++;
	return (i - start);
}

size_t	skip_token(t_tokeniserinternal *meta, char *str, size_t i)
{
	size_t	start;
	// char	quote;

	start = 0;
	start = i;
	i = token_skip_whitespace(str, start);
	if (ft_strchr("<>&|", str[i]))
		i += skip_potential_double(str, i);
	else if (ft_strchr("();", str[i]))
		i++;
	else if (str[i] == '\n' && i > 0 && str[i - 1] != '\\')
		i++;
	else
		i += skip_word(meta, str, i, 0);
	return (i - start);
}