/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/01 11:24:27 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token(t_tokentype type, char *raw_token)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	tok->raw = raw_token;
	tok->type = type;
	tok->heredoc_deliminator = 0;
	tok->variables_expanded = 0;
}

void	destroy_token(t_token **token, void (*del_raw)(char *))
{
	if (!token || !*token)
		return ;
	if ((*token)->raw && del_raw)
		del_raw((*token)->raw);
	free((*token));
	*token = 0;
}
