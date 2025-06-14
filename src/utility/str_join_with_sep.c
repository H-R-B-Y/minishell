/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join_with_sep.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:44:38 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/14 16:10:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*str_join_with_sep(const char *str1, const char *str2, const char *sep)
{
	char	*out;
	size_t	lengths[3];

	if (!str1 || !str2 || !sep)
		return ((void *)0);
	lengths[0] = ft_strlen(str1);
	lengths[1] = ft_strlen(str2);
	lengths[2] = ft_strlen(sep);
	out = malloc(sizeof(char) * (lengths[0] + lengths[1] + lengths[2] + 1));
	if (!out)
		return ((void *)0);
	out[lengths[0] + lengths[1] + lengths[2]] = '\0';
	ft_memmove(out, str1, lengths[0]);
	ft_memmove(out + lengths[0], sep, lengths[2]);
	ft_memmove(out + lengths[0] + lengths[2], str2, lengths[1]);
	return (out);
}
