/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:53:26 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/11 12:14:46 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	skip_quoted(char *str, size_t i);
size_t	skip_potential_double(char *str, size_t i);
size_t	skip_word(char *str, size_t i);

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
	char	quote;

	start = 0;
	start = i;
	i += token_skip_whitespace(str, start);
	if (str[i] == '\'' || str[i] == '"')
	{
		quote = str[i];
		ft_lstadd_back(&meta->parse_stack,
			ft_lstnew(ETOPTR EXPECT_QUOTE + (1 * (str[i] == '"'))));
		i += skip_quoted(str, i);
		if (str[i] == quote)
			POPCONT;
	}
	else if (ft_strchr("<>&|", str[i]))
		i += skip_potential_double(str, i);
	else if (ft_strchr("();", str[i]))
		i++;
	else if (str[i] == '\n' && i > 0 && str[i - 1] != '\\')
		i++;
	else
		i += skip_word(str, i);
	return (i - start);
}