/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:01:18 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/25 12:48:03 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "fsm_tokeniser.h"

char	*mark_quotes(const char *expanded);

#define _MSG "%d: %s\n"
#define WRITE_MSG(idx, str) printf(_MSG, idx, str)
#define TOKENSTR "%zu: {\"type\":\"%s\",\"raw\":\"%s\"}\n"
#define PRNT_TOK(idx, token) \
{\
	char *tmp; \
	tmp = mark_quotes(token->raw); \
	printf(TOKENSTR, idx, toktypes[token->type], tmp);\
	free(tmp); \
}

static char *toktypes[TOK_COUNT] = {
	[TOK_NONE] = "NONE",
	[TOK_WORD] = "WORD",
	[TOK_PIPE] = "PIPE",
	[TOK_REDIR_OUT] = "OUT",
	[TOK_REDIR_APPEND] = "APPEND",
	[TOK_REDIR_IN] = "IN",
	[TOK_HEREDOC] = "HEREDOC",
	[TOK_AFTER] = "AFTER",
	[TOK_AND_IF] = "AND",
	[TOK_OR_IF] = "OR",
	[TOK_LPAREN] = "LPAREN",
	[TOK_RPAREN] = "RPAREN",
	[TOK_AMP] = "AMP",
	[TOK_EOF] = "EOF",
	[TOK_INCOMPLETE_STRING] = "INCOMPLETE",
	[TOK_REDIR_FD] = "FD",
	[TOK_ERR] = "ERR",
};

static char *codes[TOKENISER_RETURNCODE_COUNT] = {
	[PARSE_OK] = "OK",
	[PARSE_CONT] = "CONT",
	[PARSE_ERROR] = "ERROR",
	[PARSE_FATAL] = "FATAL",
	[PARSE_NOTHING] = "EMPTY",
};

static void	write_tokens(int argc, t_fsmdata *data)
{
	t_list	*list;
	t_list	*iter;
	size_t	list_size;
	size_t	idx;

	if (!data)
		return ;
	list = fsm_pop_list(data);
	/*
	I would like to print them in like JSON so it can be parsed later on.
	*/

	list_size = ft_lstsize(list);
	WRITE_MSG(argc, "token count");
	printf("%zu\n", list_size);
	iter = list;
	idx = 0;
	WRITE_MSG(argc, "start tokens");
	while (iter)
	{
		t_token	*token;
		token = iter->content;
		PRNT_TOK(idx, token);
		iter = iter->next;
		idx++;
	}
	WRITE_MSG(argc, "end tokens");
	free_token_list(list, free);
}


/*
So I want to make a simple tokeniser test main, 
we init a new tokeniser.
We loop through all the argv strings, and put them all into the tokniser
and we want to print a nice and simple text
(that can be strcmp to check validity)
that tells us what the output of state of the tokeniser is.
*/

int main(int argc, char **argv)
{
	t_fsmdata		fsm_data;
	t_tokretcode	code;


	if (argc < 2)
		return (1);
	fsm_data = (t_fsmdata){.state = ST_STRT,0};
	while (--argc)
	{
		code = tokenise(&fsm_data, argv[argc]);
		WRITE_MSG(argc, codes[code]);
		switch (code)
		{
			case PARSE_OK:
				write_tokens(argc, &fsm_data);
				break;
			case PARSE_CONT:
				continue;
			case PARSE_FATAL:
				WRITE_MSG(argc, strerror(errno));
				break;
			case PARSE_ERROR:
				WRITE_MSG(argc, fsm_data.str_cond);
				break;
			case PARSE_NOTHING:
				continue;
			default:
				break;
		}
		reset_fsm(&fsm_data);
	}
	return (0);
}
