/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_skipping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:42:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/10 23:27:09 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

void	tokeniser_skip_whitespace(t_tokint *tokeniser, const char *str)
{
	if (!str || !*str)
		return ;
	if (tokeniser->current_type != TOK_INCOMPLETE_STRING)
	{	
		while (ft_iswhitespace(str[tokeniser->index_start]))
			tokeniser->index_start++;
	}
	tokeniser->index_end = tokeniser->index_start;
}
