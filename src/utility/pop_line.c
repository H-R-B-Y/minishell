/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:45:56 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/16 17:34:39 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *_pop_line(char ***arr)
{
	char	*str;

	str = (*arr)[0];
	ft_memmove((*arr), &(*arr)[1],
		(ft_arrlen((void *)&(*arr)[1]) + 1) * sizeof(char *));
	if (ft_arrlen((void *)(*arr)) == 0)
	{
		free(*arr);
		(*arr) = 0;
	}
	return (str);
}
