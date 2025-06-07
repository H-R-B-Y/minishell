/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting_next_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:16:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/07 14:57:15 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	split_extra_lines(t_readline_data *data, char *str)
{
	char	**split;
	char	*temp;

	if (!data->current_hist_item)
		temp = ft_strdup(str);
	else
		temp = str_join_with_sep(data->current_hist_item, str, "\n");
	free(data->current_hist_item);
	data->current_hist_item = temp;
	split = ft_split(str, '\n');
	data->extra_lines = split;
	data->extra_line_count = ft_arrlen((void *)split);
	return (data->extra_line_count);
}

int	next_line(t_readline_data *data, char *prompt)
{
	char	*temp;

	if (data->extra_line_count)
	{
		if (data->last_line)
			ft_dirtyswap((void *)&data->last_line, (void *)0, free);
		data->last_line = _pop_line(&data->extra_lines);
		data->extra_line_count--;
		if (data->last_line)
			return (READ_OK);
		return (READ_ERROR);
	}
	temp = readline(prompt);
	if (!temp)
		return (READ_EOF);
	if (!*temp)
		return (READ_NOTHING);
	split_extra_lines(data, temp);
	free(temp);
	return (next_line(data, prompt));
}
