/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:32:10 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/10 17:56:43 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_token_list(t_list *list)
{
	t_list *next;

	next = list;
	while (next)
	{
		print_token(next->content, 25);
		next = next->next;
	}
}

void	append_anon_token(t_tokeniserinternal *meta, t_tokentype type, char *str)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	*tok = (t_token){.heredoc_deliminator=0,.raw=str,.type=type};
	ft_lstadd_back(&meta->tokens, ft_lstnew(tok));
}
