/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prep_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:41:21 by cquinter          #+#    #+#             */
/*   Updated: 2025/09/05 21:43:06 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// /**
//  * @brief token type struct, provides information about a token
//  * @param type the type of this token
//  * @param raw the raw string for the token
//  * @param heredoc_delim This token is a heredoc deliminator
//  * @param redirect_file this token is a filename for a redirect
//  * @param quotes_removed if the quotes in the raw string have been removed
//  * @param variables_expanded This token has had its variables expanded
//  */
// typedef struct s_token			t_token;
// struct s_token
// {
// 	/// @brief the type of this token
// 	t_tokentype	type;
// 	/// @brief the raw token string
// 	char		*raw;
// 	char		**words;
// 	size_t		n_words;
// };

void	xpnd_param_var(t_xpnd_info *info)
{
	size_t	i;
	ssize_t	i2;
	size_t	new_wc;
	size_t	old_wc;
	t_minishell *shell;
	char	**words;
	
	if (!info && !info->token)
		return ;
	shell = info->shell;
	old_wc = info->tknxthread;
	i = 0;
	new_wc = 0;
	while (i < old_wc + new_wc)
	{
		i2 = -1;
		words = expand_and_split(shell, info->token[i - new_wc][0].raw, 3);
		if (!words)
			_free_arr_perror_exit(shell, (void **)info->xpnded_words, "minishell: expand");
		while (words[++i2])
			ft_dirtyswap((void *)&info->xpnded_words,
				ft_arradd_atindex((void **)info->xpnded_words, words[i2], i + i2), free);
		free(words);
		i += i2;
		new_wc += i2 - 1;
	}
	info->tknxthread += new_wc;
}

char	**glob_word(t_minishell *shell, char *str);

void	filename_expansion(t_minishell *shell, t_astnode *node,
	char ***argv, size_t *n)
{
	size_t	i;
	size_t	i2;
	size_t	new_wc;
	char	**words;

	(void)node;
	if (!argv || !*argv)
		return ;
	i = 0;
	new_wc = 0;
	while (i < *n + new_wc)
	{
		i2 = 0;
		words = glob_word(shell, (*argv)[i]);
		if (!words && ++i)
			continue ;
		ft_dirtyswap((void *)&((*argv)[i]), words[i2++], free);
		while (i2 < ft_arrlen((void *)words) && ++i2)
			ft_dirtyswap((void *)argv, ft_arradd_atindex((void **)*argv,
					words[i2 - 1], i + (i2 - 2)), free);
		free(words);
		i += i2;
		new_wc += i2 - 1;
	}
	*n += new_wc;
}

void	quote_removal(t_minishell *shell, t_astnode *node,
	char ***argv, size_t *n)
{
	size_t	i;

	(void)node;
	if (!argv)
		return ;
	i = 0;
	while (i < *n)
	{
		if (!ft_dirtyswap((void **)(argv[0] + i), rem_quotes(argv[0][i]), free))
			_free_arr_perror_exit(shell, (void **)argv, "minishell: expand");
		i++;
	}
}
