/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_dbg.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:40:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/14 17:46:52 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_DBG_H
# define V_DBG_H

# ifndef FD_DBG
#  define FD_DBG 0
# endif

# include "libft.h"

/**
 * @brief All the types of data that are written to the debug file
 */
enum	e_datatype
{
	/// @brief The following data is nothing
	DBG_DT_NONE,
	/// @brief The following data is a state
	DBG_DT_STATE,
	/// @brief The following data is informaton about a token
	DBG_DT_TOKEN_INFO,
	/// @brief The following data is a token
	DBG_DT_TOKEN,
	/// @brief The following token is an AST Node
	DBG_DT_NODES,
	/// @brief The following data is a redirect
	DBG_DT_REDR,
	/// @brief End of command stream, read for next command
	DBG_DT_DONE,
	/// @brief Count of states
	DBG_DT_COUNT,
};

/**
 * @brief info about the debugger
 */
struct	s_dbg_info
{
	/// @brief Flag for when the FD macro is set
	short	fd_available;
	/// @brief Flag for when the FD macro points to a writable fd
	short	fd_writable;
	/// @brief the filedescriptor to write too
	int		fd;
	/// @brief The states collected from the current command
	t_list	*states;
	/// @brief The tokens that make up the current command
	t_list	*tokens;
	/// @brief The nodes that make up the current command
	t_list	*nodes;
};

/**
 * @brief Initialise the debugger information
 * @param s_dbg_info Pointer to the debugger info struct
 * @returns -1 on error
 */
int			init_debugger(struct s_dbg_info *info);

/**
 * @brief Add a state to the list of states attributed to the current command
 * 
 * @param info the debugger info
 * @param state the state to add
 * @return size_t returns 1 on success
 */
size_t		dbg_add_state(struct s_dbg_info *info, int state);

/**
 * @brief Write states to the debugger fd
 * 
 * @param info the information about the debug interface 
 * @return size_t 1 Size of data written
 */
size_t		dbg_write_states(struct s_dbg_info *info);

typedef struct s_token		t_token;

/**
 * @brief Add a token to the list of tokens attributed to the current command
 * 
 * @param info the information about the debug interface
 * @param token the token to add
 * @return size_t size of data written
 */
size_t		dbg_add_token(struct s_dbg_info *info, t_token *token);

/**
 * @brief Write the tokens to the debug fd
 * 
 * @param info the information about the debug interface 
 * @return size_t size of data written
 */
size_t		dbg_write_tokens(struct s_dbg_info *info);

typedef struct s_astnode	t_astnode;

/**
 * @brief Add an AST Node to the list of nodes attributed to the current command
 * 
 * @param info The information about the debug interface
 * @param node the node to add to the list
 * @return size_t 1 on success
 */
size_t		dbg_add_nodes(struct s_dbg_info *info, t_astnode *node);

/**
 * @brief Write the nodes attributed to the current command to the debug fd
 * 
 * @param info The information about the debug interface
 * @return size_t size of data written
 */
size_t		dbg_write_nodes(struct s_dbg_info *info);

/**
 * @brief Add a token to the list of tokens attributed to the current command
 * 
 * @param info The information about the debug interface
 * @param tk the token to add to the list of tokens
 */
void		dbg_add_token_list(struct s_dbg_info *info, t_list *tk);

/**
 * @brief Write the AST to the debug interface
 * 
 * @param info The information about the debug interface
 * @param head The head of the tree
 */
void		dbg_add_ast(struct s_dbg_info *info, t_astnode *head);

/**
 * @brief Write end of command sequence to the debug fd
 * 
 * @param info the information about the debug interface
 * @return size_t size of data written
 */
size_t		dbg_write_end(const struct s_dbg_info *info);

#endif