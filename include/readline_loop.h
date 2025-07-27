/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:07:29 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/27 20:47:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_LOOP_H
# define READLINE_LOOP_H

# include "libft.h"

typedef struct s_minishell		t_minishell;

typedef enum e_readline_retcode	t_readline_retcode;
enum e_readline_retcode
{
	/// @brief Initial state for reading
	READ_START,
	/// @brief Line was read / tokenised ok
	READ_OK,
	/// @brief Nothing was read from input (empty)
	READ_NOTHING,
	/// @brief Input was closed
	READ_EOF,
	/// @brief An error was encountered in reading or tokenisation
	READ_ERROR,
	/// @brief Parsing failed
	READ_BADPARSE,
	/// @brief Fatal error do not continue
	READ_FATAL,
	/// @brief Count of possible return codes
	READ_RETCODE_COUNT
};

typedef struct s_readline_data	t_readline_data;
struct s_readline_data
{
	/// @brief Any extra lines that were read from readline
	char				**extra_lines;
	/// @brief The count of extra lines
	size_t				extra_line_count;
	/// @brief The current history item
	char				*current_hist_item;
	/// @brief The most recent line read from readline/extra_lines
	char				*last_line;
	/// @brief Reference to the interactive mode flag in shell struct.
	const short int		*interactive_mode;
};

/**
 * @brief Splits extra lines when multiple lines read from readline
 * 
 * @param data reference to the our internal information
 * @param str 
 * @return ssize_t 
 */
ssize_t	split_extra_lines(t_readline_data *data, char *str);

/**
 * @brief Gets the next line
 * 
 * This function is used to get the next line, 
 * while readline does usually return a single line,
 * this is not the case when multiple lines are pasted into
 * readline, or when a history item is loaded that contains multiple lines
 * so this function manages a buffer of lines that were potentially returned
 * from readline.
 * 
 * @param data reference to the internal information
 * @param prompt the prompt to use when using readline (if applicable)
 * @return int readline retcode
 */
int		next_line(t_readline_data *data, const char *prompt);

/**
 * @brief pop a string from a string array
 * 
 * @param arr the array of string to pop from
 * @return char* the string from the array
 * @warning Assumes that the array is freeable
 */
char	*_pop_line(char ***arr);

/**
 * @brief Readline loop that will only
 * return when a valid list of tokens is produced
 * 
 * @param shell reference to the shell
 * @return int status code (readline_retcode)
 */
int		read_until_complete_command(t_minishell *shell);

/**
 * @brief Append to (or create) the current history item
 * 
 * @param data reference to the internal information 
 * @param str pointer to the string to append to the history item
 * @return ssize_t 
 */
ssize_t	append_to_history_item(t_readline_data *data, char **str);

/**
 * @brief wrapper for readline so we dont echo when not in interactive mode.
 * 
 * @param data reference to the internal information
 * @param prompt the prompt to use for readline (if applicable)
 * @return char* the next line from the stdin
 */
char	*readline_wrapper(t_readline_data *data, const char *prompt);

#endif
