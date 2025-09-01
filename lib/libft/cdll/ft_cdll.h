/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdll.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:02:28 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/28 14:35:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CDLL_H
# define CDLL_H

# include <sys/types.h>
# include <stdlib.h>

# include "ft_mem.h"
# define CALLOC ft_calloc

typedef struct s_cdll		t_cdll;

struct s_cdll
{
	/// @brief The head of the cdll
	struct s_cdll_node			*head;
	/// @brief The tail of the cdll
	struct s_cdll_node			*tail;
	/// @brief The count of nodes in the cdll
	size_t						count;
};

struct s_cdll_node
{
	/// @brief Next node
	struct s_cdll_node	*next;
	/// @brief Previous node
	struct s_cdll_node	*prev;
	/// @brief Pointer to data
	void				*data;
};

/**
 * @brief Initialise a new cdll
 * 
 * @note this needs to return the struct not the pointer to heap allocation
 * 
 * @return t_cdll* The new cdll
 */
t_cdll				*cdll_init(void);

/**
 * @brief Delete a cdll object
 * 
 * @param list Pointer to a pointer to the list
 * @param del the function used to delete node contents
 */
void				cdll_delete(t_cdll **list,
						void (*del)(void *));

/**
 * @brief Function to initialise a new cdll node
 * 
 * @param data value to set as data in the new node
 * @return struct s_cdll_node* new cdll node
 */
struct s_cdll_node	*cdll_init_node(void *data);

/**
 * @brief delete a cdll node and free its content
 * 
 * @param node pointer to a pointer to the node
 * @param del function to free the nodes content
 */
void				cdll_delete_node(struct s_cdll_node **node,
						void (*del)(void *));

/**
 * @brief Push a node to the front of the list
 * 
 * @param list the list to push too
 * @param node the node to push
 * @return size_t cant remember what this returns?
 * TODO: update the return value in this comment
 */
size_t				cdll_push_front(t_cdll *list, struct s_cdll_node *node);

/**
 * @brief Push a node to the back of the list
 * 
 * @param list the list to push too
 * @param node the node to push
 * @return size_t cant remember what this returns
 * TODO: update the return value in this comment
 */
size_t				cdll_push_back(t_cdll *list, struct s_cdll_node *node);

/**
 * @brief Pop a value from the front of a list =
 * 
 * @param list the list to pop from
 * @return struct s_cdll_node* the node popped from the list
 */
struct s_cdll_node	*cdll_pop_front(t_cdll *list);

/**
 * @brief Pop a value from the back of the list
 * 
 * @param list the list to pop a value from
 * @return struct s_cdll_node* the node popped from the list
 */
struct s_cdll_node	*cdll_pop_back(t_cdll *list);

/**
 * @brief Get the node at a given index
 * 
 * @param stack the list to pop from
 * @param i the index in the list to pop from
 * @return struct s_cdll_node* the node at that point
 * TODO: update this comment, does the node get removed from the list?
 */
struct s_cdll_node	*cdll_get(t_cdll *list, size_t i);

#endif
