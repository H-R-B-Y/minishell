/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 00:49:53 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/26 10:52:44 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"

void	ft_arrfree(void **chunks)
{
	void	**ch;

	if (!chunks)
		return ;
	ch = chunks;
	while (*chunks)
	{
		free(*chunks);
		*chunks = 0;
		chunks++;
	}
	free(ch);
}
