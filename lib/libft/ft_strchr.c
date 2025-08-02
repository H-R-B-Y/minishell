/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:21:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/02 18:35:14 by cquinter         ###   ########.fr       */
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
