/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting_next_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:16:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/07 17:36:43 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_global_signal;

ssize_t	append_to_history_item(t_readline_data *data, const char *str)
{
	char	*temp;

	if (!str)
		return (0);
	if (!data->curr_hst_item && str[0] != '\n')
		temp = ft_strdup(str);
	else if (data->hdoc
		|| data->fsm_data->tok_int.curr_type == TOK_INCOMPLETE_STRING)
	{
		if (!last_newline_not_end(data->curr_hst_item))
			*ft_strrchr(data->curr_hst_item, '\n') = '\0';
		temp = str_join_with_sep(data->curr_hst_item, str, "\n");
	}
	else if (str[0] == '\n')
		temp = str_join_with_sep(data->curr_hst_item, str + 1, NULL);
	else if (data->fsm_data->paren_count != 0)
		temp = str_join_with_sep(data->curr_hst_item, str, "; ");
	else
		temp = str_join_with_sep(data->curr_hst_item, str, " ");
	if (!temp)
		return (-1);
	return (ft_dirtyswap((void *)&data->curr_hst_item, temp, free), 1);
}

char	*remove_newline(char *str)
{
	return (ft_strrtrim(str, "\n"));
}

ssize_t	split_extra_lines(t_readline_data *data, char *str)
{
	char	**split;

	split = simple_split(str, data);
	if (!split)
		return (-1);
	data->extra_lines = split;
	data->extra_line_count = ft_arrlen((void *)split);
	return (data->extra_line_count);
}

static int	_pop_extra(t_readline_data *data)
{
	if (data->last_line)
		ft_dirtyswap((void *)&data->last_line, (void *)0, free);
	data->last_line = _pop_line(&data->extra_lines);
	data->extra_line_count--;
	if (!data->last_line)
		return (READ_FATAL);
	else if (!*data->last_line)
		return (READ_NOTHING);
	append_to_history_item(data, data->last_line);
	return (READ_OK);
}

int	next_line(t_readline_data *data, const char *prompt)
{
	char	*temp;
	ssize_t	code;

	if (data->extra_line_count)
		return (_pop_extra(data));
	temp = readline_wrapper(data, prompt);
	if (!temp)
		return (READ_EOF);
	if (!*temp && (!data->last_line || g_global_signal))
		return (free(temp), READ_NOTHING);
	code = split_extra_lines(data, temp);
	free(temp);
	if (code)
		return (next_line(data, prompt));
	return (READ_FATAL);
}
