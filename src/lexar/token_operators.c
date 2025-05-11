/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:12:14 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/06 11:19:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

const char	*operators(void)
{
	static const char	*operators = "<>;&|()";

	return (operators);
}

int	isoperator(char c)
{
	return (!!(unsigned long int)ft_strrchr(operators(), c));
}
