/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_dbg.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:40:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/27 20:44:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_DBG_H
# define V_DBG_H

# ifndef FD_DBG
#  define FD_DBG 0
# endif

# include "libft.h"

enum	e_datatype
{
	DBG_DT_NONE,
	DBG_DT_STATE,
	DBG_DT_TOKEN_INFO,
	DBG_DT_TOKEN,
	DBG_DT_NODES,
	DBG_DT_REDR,
	DBG_DT_DONE,
	DBG_DT_COUNT,
};

struct	s_dbg_info
{
	short	fd_available;
	short	fd_writable;
	int		fd;
	t_list	*states;
	t_list	*tokens;
	t_list	*nodes;
};

int			init_debugger(struct s_dbg_info *info);

size_t		dbg_add_state(struct s_dbg_info *info, int state);
size_t		dbg_write_states(struct s_dbg_info *info);

typedef struct s_token		t_token;
size_t		dbg_add_token(struct s_dbg_info *info, t_token *token);
size_t		dbg_write_tokens(struct s_dbg_info *info);

typedef struct s_astnode	t_astnode;
size_t		dbg_add_nodes(struct s_dbg_info *info, t_astnode *node);
size_t		dbg_write_nodes(struct s_dbg_info *info);

void		dbg_add_token_list(struct s_dbg_info *info, t_list *tk);
void		dbg_add_ast(struct s_dbg_info *info, t_astnode *head);

size_t		dbg_write_end(const struct s_dbg_info *info);

#endif