/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_dbg.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:40:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/28 15:05:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_DBG_H
# define V_DBG_H

# ifndef DBG_FD
#  define DBG_FD 0
# endif

#include "libft.h"

enum	e_datatype
{
	DBG_DT_STATE,
	DBG_DT_TOKEN,
	DBG_DT_NODES,
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

int	add_state(struct s_dbg_info *info, int state);
int	write_states(struct s_dbg_info *info);

typedef struct s_token	t_token;
int	add_token(struct s_dbg_info *info, t_token *token);
int	write_tokens(struct s_dbg_info *info);

typedef struct s_astnode		t_astnode;
int	add_nodes(struct s_dbg_info *info, t_astnode *node);
int	write_nodes(struct s_dbg_info *info);

#endif