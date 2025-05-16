/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_skipping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:42:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/16 11:23:49 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

void	tokeniser_skip_whitespace(t_tokint *tokeniser, char *str)
{
	if (!str || !*str)
		return ;
	while (ft_iswhitespace(str[tokeniser->index_start]))
		tokeniser->index_start++;
	tokeniser->index_end = tokeniser->index_start;
}
