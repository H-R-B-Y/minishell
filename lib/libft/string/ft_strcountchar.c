/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcountchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:05:19 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 11:04:25 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

ssize_t	ft_strcountchar(const char *str, char c)
{
	size_t	count;
	size_t	idx;

	if (!str)
		return (-1);
	idx = 0;
	count = 0;
	while (str[idx])
		count += 1 * (str[idx++] == c);
	return (count);
}
