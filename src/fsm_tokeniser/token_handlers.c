/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:37:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/24 13:49:40 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		skip_token_str(t_tokint *tokeniser, const char *str);

void	handle_potential_redirect(t_tokint *tokeniser, const char *str)
{
	char	t;

	while (str[tokeniser->i_end] && isdigit(str[tokeniser->i_end]))
		tokeniser->i_end++;
	t = str[tokeniser->i_end];
	if (!(t == '<' || t == '>'))
	{
		skip_token_str(tokeniser, str);
		return ;
	}
	tokeniser->i_end++;
	if (str[tokeniser->i_end] == t)
		tokeniser->i_end++;
	else if (str[tokeniser->i_end] == '&')
	{
		tokeniser->i_end++;
		while (ft_iswhitespace(str[tokeniser->i_end]))
			tokeniser->i_end++;
		if (ft_isdigit(str[tokeniser->i_end]))
			while (str[tokeniser->i_end] 
				&& (ft_isdigit(str[tokeniser->i_end])))
				tokeniser->i_end++;
		else if (str[tokeniser->i_end] == '-')
			tokeniser->i_end++;
	}
}

void	handle_operator(t_tokint *tokeniser, const char *str)
{
	char	c;

	c = str[tokeniser->i_end];
	if (ft_isdigit(c) || c == '>' || c == '<')
		handle_potential_redirect(tokeniser, str);
	else if (c == '&' && str[tokeniser->i_end + 1] == '>')
		tokeniser->i_end += 2 + (1 * (str[tokeniser->i_end + 1]
					== str[tokeniser->i_end + 2]));
	else if (!ft_strchr(";()", c)
		&& c == str[tokeniser->i_end + 1])
		tokeniser->i_end = tokeniser->i_end + 2;
	else
		tokeniser->i_end = tokeniser->i_end + 1;
}

int	handle_unclosed_quote(t_tokint *tokeniser, const char *str)
{
	char	*temp;
	
	temp = ft_substr(str, tokeniser->i_start,
			tokeniser->i_end - tokeniser->i_start);
	if (!temp)
		return (0);
	if (!tokeniser->prev_line)
		ft_dirtyswap((void *)&tokeniser->prev_line,
			str_vec_join((char *[2]){temp, 0}), free);
	else if (last_newline_not_end(tokeniser->prev_line))
		ft_dirtyswap((void *)&tokeniser->prev_line,
			str_vec_join((char *[4]){tokeniser->prev_line, "\n", temp, 0}),
			free);
	else
		ft_dirtyswap((void *)&tokeniser->prev_line,
			str_vec_join((char *[3]){tokeniser->prev_line, temp, 0}),
			free);
	free(temp);
	if (!tokeniser->prev_line)
		return (0);
	return (1);
}

int	handle_token_type(t_fsmdata *fsm)
{
	if (fsm->tok_int.curr_type == TOK_LPAREN)
		fsm->paren_count++;
	if (fsm->tok_int.curr_type == TOK_RPAREN)
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
