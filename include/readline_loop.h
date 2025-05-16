/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:07:29 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/16 17:33:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_LOOP_H
# define READLINE_LOOP_H

# include "libft.h"

typedef enum e_readline_retcode	t_readline_retcode;
enum e_readline_retcode
{
	READ_OK,
	READ_ERROR, // split this out later into different issues
	READ_RETCODE_COUNT
};

typedef struct s_readline_data	t_readline_data;
struct s_readline_data
{
	char	**extra_lines;
	size_t	extra_line_count;
	char	*current_hist_item;
	char	*last_line;
};

size_t	split_extra_lines(t_readline_data *data, char *str);

int		next_line(t_readline_data *data, char *prompt);

char	*_pop_line(char ***arr);

#endif
