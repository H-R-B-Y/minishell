/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:13:45 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/13 17:15:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tokeniser_set_error(t_tokeniserinternal *meta, char *error)
{
	meta->state = PARSE_ERROR;
	meta->error_reason = error;
}
