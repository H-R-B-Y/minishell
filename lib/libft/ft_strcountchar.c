/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcountchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:05:19 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/07 18:07:18 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

size_t	ft_strcountchar(char *str, char c)
{
	size_t	count;
	size_t	idx;

	idx = 0;
	count = 0;
	while (str[idx])
		count += 1 * (str[idx++] == c);
	return (count);
}
