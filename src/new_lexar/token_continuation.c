/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_continuation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:39:56 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/13 18:49:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_continuation(t_tokeniserinternal *meta,
			t_tokentype type)
{
	// we do not need to do anything for NONE WORD AFTER AMP and END
	// Escape sequences are octal so they need to be converted
	if ((type == TOK_WORD || type == TOK_LPAREN || type == TOK_REDIR_IN || type == TOK_HEREDOC)
		&& meta->parse_stack && ft_strchr("\1\2",
		(PTRTOE ft_lstlast(meta->parse_stack)->content))) 
		POPCONT;
	else if (type == TOK_RPAREN)
	{
		if (!meta->parse_stack || (PTRTOE ft_lstlast(meta->parse_stack)->content) != EXPECT_PAREN)
			tokeniser_set_error(meta, ft_strdup("PARSE ERROR : unexpected right parenthesis"));
		else
			POPCONT;
	}
	if (ft_strchr("\0\7\14\15\16", type)) // escape codes to reduce code size
		return ;
	if (type == TOK_PIPE || type == TOK_AND_IF || type == TOK_OR_IF
		|| type == TOK_REDIR_IN || type == TOK_REDIR_OUT)
		ft_lstadd_back(&meta->parse_stack, ft_lstnew(ETOPTR EXPECT_WORD));
	else if (type == TOK_HEREDOC)
		ft_lstadd_back(&meta->parse_stack, ft_lstnew(ETOPTR EXPECT_HEREDOC));
	else if (type == TOK_LPAREN)
		ft_lstadd_back(&meta->parse_stack, ft_lstnew(ETOPTR EXPECT_PAREN));

}
