/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:32:10 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/08 12:32:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_token_list(t_list *list)
{
	t_list *next;

	next = list;
	while (next)
	{
		print_token(next->content, 25);
		next = next->next;
	}
}
