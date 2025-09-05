/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:59:55 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/01 12:27:10 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FT_INCLUDE_ALL
#include "libft.h"

// NOTE: add to libft 
void	*arrjoin(void **vec1, void **vec2)
{
	size_t	size;
	void	**out;

	size = ft_arrlen(vec1) + ft_arrlen(vec2);
	out = ft_calloc(size + 1, sizeof(void *));
	ft_memmove(out, vec1, ft_arrlen(vec1) * sizeof(void *));
	ft_memmove(out + ft_arrlen(vec1), vec2, ft_arrlen(vec2) * sizeof(void *));
	return (out);
}
