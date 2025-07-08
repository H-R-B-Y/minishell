/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcountchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:05:19 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/08 13:03:52 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

size_t	ft_strcountchar(const char *str, char c)
{
	size_t	count;
	size_t	idx;

	idx = 0;
	count = 0;
	while (str[idx])
		count += 1 * (str[idx++] == c);
	return (count);
}
