/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prep_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:41:21 by cquinter          #+#    #+#             */
/*   Updated: 2025/09/07 23:09:16 by cquinter         ###   ########.fr       */
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
	size_t	new_wc;
	size_t	tkn_c;
	t_minishell *shell;
	t_token *crr_token;
	
	if (!info && !info->token)
		return ;
	shell = info->shell;
	tkn_c = info->tknxthread;
	i = 0;
	new_wc = 0;
	while (i < tkn_c)
	{
		crr_token = info->token[i];
		crr_token->words = expand_and_split(shell, crr_token->raw, 3);
		new_wc += ft_arrlen((void **)crr_token->words);
		i++;
	}
	info->new_wc = new_wc;
}

char	**glob_word(t_minishell *shell, char *str);

void	filename_expansion(t_xpnd_info *info)
{
	size_t	i;
	size_t	i2;
	size_t	i3;
	size_t	new_wc;
	size_t	tkn_c;
	t_minishell *shell;
	t_token *crr_token;
	char **temp_w;
	
	if (!info && !info->token)
		return ;
	shell = info->shell;
	tkn_c = info->tknxthread;
	i = 0;
	new_wc = 0;
	while (i < tkn_c)
	{
		i2 = 0;
		crr_token = info->token[i];
		while(crr_token->words && crr_token->words[i2])
		{
			temp_w = glob_word(shell, crr_token->words[i2]);
			if (!temp_w && ++i2)
				continue;
			i3 = 0;
			ft_dirtyswap((void *)&crr_token->words[i2], temp_w[i3++], free);
			while (temp_w[i3])
				ft_dirtyswap((void **)&crr_token->words,
						ft_arradd_atindex((void **)crr_token->words, temp_w[i3++], i2++), free);
			free(temp_w);
		}
		new_wc += i2;
		i++;
	}
	info->new_wc = new_wc;
}

void	quote_removal(t_xpnd_info *info)
{
	size_t	i;
	size_t	i2;
	size_t	new_wc;
	size_t	tkn_c;
	t_token *crr_token;
	
	if (!info && !info->token)
		return ;
	tkn_c = info->tknxthread;
	i = 0;
	new_wc = 0;
	while (i < tkn_c)
	{
		i2 = 0;
		crr_token = info->token[i];
		while(crr_token->words && crr_token->words[i2])
			rem_quotes_in_place(crr_token->words[i2++]);
		new_wc += i2;
		i++;
	}
	info->new_wc = new_wc;
}