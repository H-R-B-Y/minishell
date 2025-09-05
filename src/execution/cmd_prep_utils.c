/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prep_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:37:48 by cquinter          #+#    #+#             */
/*   Updated: 2025/09/05 23:08:12 by cquinter         ###   ########.fr       */
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
	static t_shell_expansion_fnc	shell_expansion_fnc[2] = {
		(t_shell_expansion_fnc){.f = xpnd_param_var},
		// (t_shell_expansion_fnc){.f = filename_expansion},
		// (t_shell_expansion_fnc){.f = quote_removal},
		(t_shell_expansion_fnc){.f = 0},	
	};

	return (shell_expansion_fnc);
}

void *expansion_thread(void *arg)
{
	t_shell_expansion_fnc	*xpnsion_f;
	size_t	i;
	t_xpnd_info	*info;

	if (!arg)
		return (NULL);
	info = (t_xpnd_info *)arg;
	xpnsion_f = set_expansion_fncs();
	i = 0;
	while (xpnsion_f[i].f)
	{
		xpnsion_f[i].f(info);
		i++;
	}
	return (NULL);
}




char	**cmdv_prep(t_minishell *shell, t_astnode *node)
{
	t_xpnd_info				thread[NPROCESSORS];	// TODO update cc to define NPROCESSORS - delete variable bellow
	char					**argv;
	size_t					j;
	size_t					nprocessors;
	size_t					ntoken;
	size_t					outw_i;
	size_t					xpnded_tkn_c;
	size_t					to_xpnd_tkn_c;


	if (!node)
		return (NULL);
	memset(thread, 0, NPROCESSORS * sizeof(t_xpnd_info));
	node->cmd_i = get_cmd_idx(node);
	ntoken = node->token_count;
	xpnded_tkn_c = 0;
	to_xpnd_tkn_c = 0;
	nprocessors = sysconf(_SC_NPROCESSORS_ONLN);
	
	j = 0;
	while(j < nprocessors && to_xpnd_tkn_c < ntoken)
	{
		thread[j].shell = shell;
		thread[j].tknxthread = ntoken / nprocessors;
		if (!thread[j].tknxthread)
			thread[j].tknxthread = ntoken % nprocessors;
		thread[j].token = node->tokens + j;
		to_xpnd_tkn_c += thread[j].tknxthread;
		if (pthread_create(&thread[j].t_id, NULL, expansion_thread, thread + j) == -1)
		{
			dprintf(2, "Error: did not create all threads\n");
			j++;
			break ;
		}
		j++;
	}
	
	while (j)
	{
		pthread_join(thread[--j].t_id, NULL);
		xpnded_tkn_c += thread[j].tknxthread;
	}
	
	argv = ft_calloc(xpnded_tkn_c + 1, sizeof(char *));
	if (!argv)
		perror_exit(shell, "at cmdv_prep");
	while (j < ntoken && thread[j].xpnded_words)
	{
		outw_i = 0;
		while (thread[j].xpnded_words && thread[j].xpnded_words[outw_i])
			*argv++ = thread[j].xpnded_words[outw_i++];
		free(thread[j].xpnded_words);
		j++;
	}
	node->argc = xpnded_tkn_c;
	return (argv - xpnded_tkn_c);
}
