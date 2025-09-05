/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prep_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:37:48 by cquinter          #+#    #+#             */
/*   Updated: 2025/09/05 16:56:11 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	get_cmd_idx(t_astnode *node)
{
	size_t	i;
	t_token	**t;

	if (!node)
		return (-1);
	i = 0;
	t = node->tokens;
	while (i < node->token_count
		&& ft_strchr_i(t[i][0].raw, '=') != (size_t)-1
		&& ft_strchr_i(t[i][0].raw, '=') != 0)
	{
		if (ft_strchr_i(t[i][0].raw, '=') > ft_strchr_i(t[i][0].raw, '"') ||
			ft_strchr_i(t[i][0].raw, '=') > ft_strchr_i(t[i][0].raw, '\'') ||
			ft_strchr_i(t[i][0].raw, '=') > ft_strchr_i(t[i][0].raw, '\\') ||
			ft_strchr_i(t[i][0].raw, '=') > ft_strchr_i(t[i][0].raw, ' ') ||
			ft_strchr_i(t[i][0].raw, '=') > ft_strchr_i(t[i][0].raw, ' ') ||
			ft_strchr_i(t[i][0].raw, '=') > ft_strchr_i(t[i][0].raw, '$') ||
			(t[i][0].raw[0] != '_' && !ft_isalpha(t[i][0].raw[0])))
			break ;
		i++;
	}
	if (i == node->token_count)
		return (-1);
	return (i);
}

static t_shell_expansion_fnc	*set_expansion_fncs(void)
{
	static t_shell_expansion_fnc	shell_expansion_fnc[4] = {
		(t_shell_expansion_fnc){.f = xpnd_param_var},
		(t_shell_expansion_fnc){.f = filename_expansion},
		(t_shell_expansion_fnc){.f = quote_removal},
		(t_shell_expansion_fnc){.f = 0},	
	};

	return (shell_expansion_fnc);
}

char **expansion_thread(t_token *token)
{
	t_shell_expansion_fnc	*xpnsion_f;
		
	xpnsion_f = set_expansion_fncs();
	while (xpnsion_f[i].f)
	{
		xpnsion_f[i].f(shell, node, &argv, &n);
		i++;
	}
}


#define	NPROCESSORS 20
#define INTERNAL_MAX 40
#include <limits.h>

char	**cmdv_prep(t_minishell *shell, t_astnode *node)
{
	pthread_t	*thread[NPROCESSORS];	
	char					**argv[_POSIX_ARG_MAX];
	size_t					max_thread;
	size_t					i;
	size_t					j;
	ssize_t					arg_max;
	size_t					ncreated;
	size_t					ntoken;
	char					**ret_words;

	// checks and set variables
	if (!node)
		return (NULL);
	node->cmd_i = get_cmd_idx(node);
	ntoken = node->token_count;
	arg_max = _POSIX_ARG_MAX - ft_arrlen(shell->environment)
	argv = (char *[_POSIX_ARG_MAX])
	if (!argv)
		return (NULL);
	
	// // cores = sysconf(_SC_NPROCESSORS_ONLN);
	// if (ntoken > NPROCESSORS)
	// 	max_thread = ntoken / NPROCESSORS;
	// else
	// 	max_thread = ntoken;
	// create threads
	i = 0;
	while (i < ntoken)
	{
		j = 0;
		while(j < NPROCESSORS && i + j < node->token_count)
			pthread_create(thread[j++], NULL, expansion_thread, node->tokens[0][i]); // TODO set new token vars to 
		ncreated = j;
		j = 0;
		while (j < ncreated)
		{
			pthread_join(thread[j++], ret_words); // TODO handle rets
			if (!ret_words)
			{
				dprintf(2, "thread ret NULL\n");
				continue;
			}
			while (*ret_words)
				argv[i++] = (*ret_words)++;
		}
	}
	node->argc += 
	return (argv);
}
