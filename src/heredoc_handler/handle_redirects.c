/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:49:12 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/27 19:37:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	extract_tofromfds(char *raw, char *sep, int *out)
{
	char	o[2];

	o[0] = sep[0];
	o[1] = sep[1];
	sep[0] = '\0';
	sep[1] = '\0';
	out[0] = ft_atoi(raw);
	out[1] = ft_atoi(&sep[2]);
	sep[0] = o[0];
	sep[1] = o[1];
	return ;
}

t_redirect_desc	*handle_redirectfd(t_token *redirect)
{
	t_redirect_desc	*output;
	int				fds[2];
	char			*sep;

	output = ft_calloc(1, sizeof(t_redirect_desc));
	if (!output)
		return (NULL);
	sep = ft_strchr(redirect->raw, '>');
	if (!sep)
		sep = ft_strchr(redirect->raw, '<');
	extract_tofromfds(redirect->raw, sep, fds);
	if (redirect->raw[ft_strlen(redirect->raw) - 1] != '-')
		(*output) = (t_redirect_desc){
			.type = REDIRECT_FD, .fd_map.from_fd = fds[1],
			.subtype = REDIR_FD, .fd_map.to_fd = fds[0],};
	else
		(*output) = (t_redirect_desc){
			.type = REDIRECT_FD, .fd_map.from_fd = fds[1],
			.subtype = CLOSE_FD, .fd_map.to_fd = fds[0],};
	return (output);
}

int	get_tofd(char *raw, char *sep)
{
	int		i;
	char	o;

	o = *sep;
	i = ft_atoi(raw);
	*sep = o;
	return (i);
}

t_redirect_desc	*handle_redirect(t_token *redirect, t_token *filename)
{
	t_redirect_desc	*output;
	int				to_fd;
	char			*sep;

	output = ft_calloc(1, sizeof(t_redirect_desc));
	if (!output)
		return (0);
	sep = ft_strchr(redirect->raw, '>');
	if (!sep)
		sep = ft_strchr(redirect->raw, '<');
	if (sep == redirect->raw)
		to_fd = (int [2]){0, 1}[(redirect->type != TOK_REDIR_IN)];
	else if (*redirect->raw == '&')
		to_fd = -1;
	else
		to_fd = get_tofd(redirect->raw, sep);
	(*output) = (t_redirect_desc){.type = (t_redirect_type [3]){
		REDIRECT_IN, REDIRECT_OUT, REDIRECT_OUT_A}[
		(0 * (redirect->type == TOK_REDIR_IN))
		+ (1 * (redirect->type == TOK_REDIR_OUT))
		+ (2 * (redirect->type == TOK_REDIR_APPEND))],
		.file_map.filename = ft_strdup(filename->raw), .file_map.to_fd = to_fd,
	};
	return (output);
}
