/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:21:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/01 16:24:36 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// WHO KEEPS SIGNING THESE CHARS T-T
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s && (unsigned char)*s != (unsigned char)c)
		s++;
	if ((unsigned char)*s == (unsigned char)c)
		return ((char *)s);
	return (0);
}
