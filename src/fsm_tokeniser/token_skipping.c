/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_skipping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:42:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/23 15:10:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

void	tokeniser_skip_whitespace(t_tokint *tokeniser, const char *str)
{
	if (!str || !*str)
		return ;
	if (tokeniser->curr_type != TOK_INCOMPLETE_STRING)
	{	
		while (ft_iswhitespace(str[tokeniser->i_start]))
			tokeniser->i_start++;
	}
	tokeniser->i_end = tokeniser->i_start;
}
