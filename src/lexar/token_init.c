/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/01 17:08:28 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token(t_tokentype type, char *raw_token)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	ft_bzero(tok, sizeof(t_token));
	tok->raw = raw_token;
	tok->type = type;
	return (tok);
}

void	destroy_token(t_token *token, void (*del_raw)(void *))
{
	if (!token)
		return ;
	if (token->text)
		free(token->text);
	if (token->raw && del_raw)
		del_raw(token->raw);
	free(token);
}
