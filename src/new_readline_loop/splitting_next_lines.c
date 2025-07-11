/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting_next_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:16:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/11 00:47:39 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

ssize_t	append_to_history_item(t_readline_data *data, char **str)
{
	char *temp;
	char *nlp;
	size_t	end_i;

	if (!*str)
		return (-1);
	if (!data->current_hist_item)
		temp = ft_strdup(*str);
	else
	{
		nlp = ft_strrchr(data->current_hist_item, '\n');
		end_i = ft_strlen(data->current_hist_item) - 1;
		if (!nlp || nlp != (data->current_hist_item + end_i))
			temp = str_join_with_sep(data->current_hist_item, *str, "\n");
		else
			temp = ft_strjoin(data->current_hist_item, *str);
			// ft_dirtyswap((void *)&data->last_line, ft_strrtrim(data->last_line, "\n"), free);
	}
	ft_dirtyswap((void *)&data->current_hist_item, temp, free);
	return (1);
}

size_t	split_extra_lines(t_readline_data *data, char *str)
{
	char	**split;

	split = simple_split(str, data);
	// append_to_history_item(data, str);
	data->extra_lines = split;
	data->extra_line_count = ft_arrlen((void *)split);
	return (data->extra_line_count);
}

int	next_line(t_readline_data *data, const char *prompt)
{
	char	*temp;

	if (data->extra_line_count)
	{
		if (data->last_line)
			ft_dirtyswap((void *)&data->last_line, (void *)0, free);
		data->last_line = _pop_line(&data->extra_lines);
		data->extra_line_count--;
		if (!*data->last_line)
			return (READ_NOTHING);
		// if (data->current_hist_item)
		if (data->last_line)
			return (READ_OK);
		return (READ_ERROR);
	}
	temp = readline(prompt);
	if (!temp)
		return (READ_EOF);
	if (!*temp && !data->last_line)
		return (READ_NOTHING);
	split_extra_lines(data, temp);
	free(temp);
	return (next_line(data, prompt));
}
