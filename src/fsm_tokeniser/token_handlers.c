/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:37:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/23 14:26:25 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokentype		skip_token_str(t_tokint *tokeniser, const char *str);

void	handle_potential_redirect(t_tokint *tokeniser, const char *str)
{
	char	t;

	while (str[tokeniser->index_end] && isdigit(str[tokeniser->index_end]))
		tokeniser->index_end++;
	t = str[tokeniser->index_end];
	if (!(t == '<' || t == '>'))
	{
		skip_token_str(tokeniser, str);
		return ;
	}
	tokeniser->index_end++;
	if (str[tokeniser->index_end] == t)
		tokeniser->index_end++;
	else if (str[tokeniser->index_end] == '&')
	{
		tokeniser->index_end++;
		while (ft_iswhitespace(str[tokeniser->index_end]))
			tokeniser->index_end++;
		if (ft_isdigit(str[tokeniser->index_end]))
			while (str[tokeniser->index_end] 
				&& (ft_isdigit(str[tokeniser->index_end])))
				tokeniser->index_end++;
		else if (str[tokeniser->index_end] == '-')
			tokeniser->index_end++;
	}
}

void	handle_operator(t_tokint *tokeniser, const char *str)
{
	char	c;

	c = str[tokeniser->index_end];
	if (ft_isdigit(c) || c == '>' || c == '<')
		handle_potential_redirect(tokeniser, str);
	else if (c == '&' && str[tokeniser->index_end + 1] == '>')
		tokeniser->index_end += 2 + (1 * (str[tokeniser->index_end + 1]
					== str[tokeniser->index_end + 2]));
	else if (!ft_strchr(";()", c)
		&& c == str[tokeniser->index_end + 1])
		tokeniser->index_end = tokeniser->index_end + 2;
	else
		tokeniser->index_end = tokeniser->index_end + 1;
}

int	handle_unclosed_quote(t_tokint *tokeniser, const char *str)
{
	char	*temp;
	
	temp = ft_substr(str, tokeniser->index_start,
			tokeniser->index_end - tokeniser->index_start);
	if (!temp)
		return (0);
	if (!tokeniser->previous_line)
		ft_dirtyswap((void *)&tokeniser->previous_line,
			str_vec_join((char *[2]){temp, 0}), free);
	else if (last_newline_not_end(tokeniser->previous_line))
		ft_dirtyswap((void *)&tokeniser->previous_line,
			str_vec_join((char *[4]){tokeniser->previous_line, "\n", temp, 0}),
			free);
	else
		ft_dirtyswap((void *)&tokeniser->previous_line,
			str_vec_join((char *[3]){tokeniser->previous_line, temp, 0}),
			free);
	free(temp);
	if (!tokeniser->previous_line)
		return (0);
	return (1);
}

int	handle_token_type(t_fsmdata *fsm)
{
	if (fsm->tokeniser_internals.current_type == TOK_LPAREN)
		fsm->paren_count++;
	if (fsm->tokeniser_internals.current_type == TOK_RPAREN)
		fsm->paren_count--;
	if (fsm->paren_count < 0)
		return (0);
	return (1);
}

int	handle_subshell_newline(t_fsmdata *fsm)
{
	if (!(fsm->state != ST_OPRA && fsm->state != ST_SEQ
			&& fsm->state != ST_LSSH))
		return (0);
	if (!append_anon_token(fsm, TOK_AFTER, ft_strdup(";")))
		return (-1);
	state_change(fsm, ST_SEQ);
	return (1);
}
