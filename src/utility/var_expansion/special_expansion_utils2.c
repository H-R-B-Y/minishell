/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_expansion_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 00:37:29 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/14 18:41:13 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./var_expansion.h"
#include "../../../include/minishell.h"

ssize_t	special_ansi_c_quotation(t_minishell *shell,
	const char	*value,
	char		**output
)
{
	(void)value;
	(void)shell;
	*output = ft_strdup(" ");
	ft_printf("Note: $\"\": ANSI-C escaped chars not handled (ie. \'\\n\')\n");
	return (0);
}

ssize_t	special_translation(t_minishell *shell,
	const char *value,
	char **output
)
{
	(void)value;
	(void)shell;
	*output = ft_strdup(" ");
	ft_printf("Note: $\"\": locale translation not implemented\n");
	return (0);
}
