/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_local_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:13:15 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/05 16:38:59 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*mark_quotes(const char *expanded);

static ssize_t	local_dir_glob(char ***p)
{
	DIR				*dir;
	char			*cwd;
	struct dirent	*entry;

	if (!p)
		return (-1);
	cwd = getcwd(0, 0);
	dir = opendir(cwd);
	free(cwd);
	if (!dir)
		return (-1);
	*p = ft_calloc(1, sizeof(char *));
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		ft_dirtyswap((void *)p, ft_arradd_back((void *)*p,
				ft_strdup(entry->d_name)), free);
		entry = readdir(dir);
	}
	return (closedir(dir), ft_arrlen((void *)*p));
}

char	**glob_word(t_minishell *shell, char *str) // TODO: shell for error handling?
{
	ssize_t	i;
	ssize_t	count;
	char	**words;
	char	*temp;

	if (!shell || !str)
		return (0);
	if (str[0] != '*' || str[1] != '\0')
		return (0);
	count = local_dir_glob(&words);
	i = 0;
	while (i < count)
	{
		temp = mark_quotes(words[i]);
		if (temp)
			ft_dirtyswap((void *)&words[i], temp, free);
		i++;
	}
	if (count < 0)
		return (0);
	return (words);
}
