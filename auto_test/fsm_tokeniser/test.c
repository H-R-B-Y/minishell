/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:01:18 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/29 12:50:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "fsm_tokeniser.h"

char	*mark_quotes(const char *expanded);


static char *escape_str(char *str)
{
	char *new;
	size_t len;
	size_t i;
	size_t j;

	if (!str)
		return (0);
	len = ft_strlen(str);
	new = ft_calloc(len * 2 + 1, sizeof(char));
	if (!new)
		return (0);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] == '\n')
			new[j++] = '\\', new[j++] = 'n';
		else if (str[i] == '\t')
			new[j++] = '\\', new[j++] = 't';
		else if (str[i] == '\r')
			new[j++] = '\\', new[j++] = 'r';
		else if (str[i] == '\"')
			new[j++] = '\\', new[j++] = '\"';
		else if (str[i] == '\\')
			new[j++] = '\\', new[j++] = '\\';
		else
			new[j++] = str[i];
		i++;
	}
	return (new);
}

static void write_token(t_token *tok)
{
	char	*tmp;

	if (!tok)
		return ;
	tmp = escape_str(tok->raw);
	printf("{\"type\":\"%s\",\"raw\":\"%s\"}\n",
		g_token_type_str[tok->type], tmp);
	free(tmp);
}

static void	write_tokens(int argc, t_fsmdata *data)
{
	t_list	*list;
	t_list	*iter;
	size_t	list_size;
	size_t	idx;

	(void)argc;
	if (!data)
		return ;
	list = fsm_pop_list(data);
	/*
	I would like to print them in like JSON so it can be parsed later on.
	*/

	list_size = ft_lstsize(list);
	printf("Token count: %zu\n", list_size);
	iter = list;
	idx = 0;
	while (iter)
	{
		t_token	*token;
		token = iter->content;
		write_token(token);
		iter = iter->next;
		idx++;
	}
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
	size_t			idx;

	if (argc < 2)
		return (1);
	fsm_data = (t_fsmdata){.state = ST_STRT,0};
	idx = 1;
	while (idx < (size_t)argc)
	{
		{
			char *tmp = escape_str(argv[idx]);
			printf("Input: \"%s\"\n", tmp);
			free(tmp);
		}
		code = tokenise(&fsm_data, argv[idx]);
		switch (code)
		{
			case PARSE_OK:
				printf("OK: %s\n", fsm_data.str_cond);
				write_tokens(argc, &fsm_data);
				break;
			case PARSE_CONT:
				printf("CONTINUE: %s\n", fsm_data.str_cond);
				idx++;
				continue;
			case PARSE_FATAL:
				printf("FATAL: %s\n", strerror(errno));
				break;
			case PARSE_ERROR:
				printf("ERROR: %s\n", fsm_data.str_cond);
				break;
			case PARSE_NOTHING:
				printf("NOTHING: %s\n", fsm_data.str_cond);
				idx++;
				continue;
			default:
				break;
		}
		reset_fsm(&fsm_data);
		idx++;
	}
	return (0);
}
