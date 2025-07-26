/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting_next_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:16:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/26 17:51:24 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ssize_t	append_to_history_item(t_readline_data *data, char **str)
// {
// 	char *temp;

// 	if (!*str)
// 		return (-1); // should this case be 0, then if malloc fails below we return -1? 
// 	if (!data->current_hist_item)
// 		temp = ft_strdup(*str);
// 	else
// 	{
// 		if (last_newline_not_end(data->current_hist_item))
// 			temp = str_join_with_sep(data->current_hist_item, *str, "\n");
// 		else
// 			temp = ft_strjoin(data->current_hist_item, *str);
// 	}
// 	ft_dirtyswap((void *)&data->current_hist_item, temp, free);
// 	return (1);
// }

ssize_t	append_to_history_item(t_readline_data *data, char **str)
{
	char *temp;

	if (!*str)
		return (0);
	if (!data->current_hist_item)
		temp = ft_strdup(*str);
	else
		temp = str_join_with_sep(data->current_hist_item, *str, " ");
	if (!temp)
		return (ft_dirtyswap((void *)&data->current_hist_item, temp, free), -1);
	ft_dirtyswap((void *)&data->current_hist_item, temp, free);
	return (1);
}

void	append_tokenv_to_history_item(t_minishell *shell, t_readline_data *rl_data, t_list *tokens)
{
	t_token	*token;
	t_list	*current;
	
	current = tokens;
	while (current)
	{
		token = current->content;
		if (append_to_history_item(rl_data, &token->raw) < 0)
			perror_exit(shell, "minishell: appending history");
		current = current->next;			
	}
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

int	next_line(t_readline_data *data, const char *prompt)
{
	char	*temp;
	ssize_t	code;

	if (data->extra_line_count)
	{
		if (data->last_line)
			ft_dirtyswap((void *)&data->last_line, (void *)0, free);
		data->last_line = _pop_line(&data->extra_lines);
		data->extra_line_count--;
		if (!data->last_line)
			return (READ_FATAL);
		else if (!*data->last_line)
			return (READ_NOTHING);
		return (READ_OK);
	}
	temp = readline_wrapper(data, prompt);
	if (!temp)
		return (READ_EOF);
	if (!*temp && !data->last_line)
		return (READ_NOTHING);
	code = split_extra_lines(data, temp);
	free(temp);
	if (code)
		return (next_line(data, prompt));
	return (READ_FATAL); // not possible for split extra lines to return 0 so this doesnt need a condition block
}
