/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prep_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:37:48 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/05 16:18:04 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_path_and_cmd(char ***path, char **dash_cmd, char *cmd, char **envp)
{

	*path = ft_split(s_get_fromthis_env(envp, "PATH"), ':');
	if (!*path)
		return (1);
	*dash_cmd = ft_strjoin("/", cmd);
	if (!*dash_cmd)
	{
		ft_dirtyswap((void **)path, NULL, free);
		return (1);
	}
	return (0);
}

char	*get_exec_path(t_minishell *shell, char *cmd, char **envp)
{
	char	**path = NULL;
	char	*exec_path;
	char	*dash_cmd = NULL;
	int		i;

	if (set_path_and_cmd(&path, &dash_cmd, cmd, envp))
		perror_exit(shell, "unable to set cmd");
	i = 0;
	while (path[i])
	{
		exec_path = ft_strjoin(path[i], dash_cmd);
		if (!exec_path)
		{
			free(dash_cmd);
			ft_arrclear((void **)path, free);
			perror_exit(shell, "ft_strjoin");
		}
		if (access(exec_path, F_OK) == 0)
			break ;
		free(exec_path); 
		i++;
	}
	if (!path[i])
		return(free(dash_cmd), ft_arrclear((void **)path, free), NULL);
	return(free(dash_cmd), ft_arrclear((void **)path, free), exec_path);
}

size_t get_cmd_idx(t_astnode *node)
{
	size_t	i;

	if (!node)
		return (-1);
	i = 0;
	while (i < node->token_count &&
		ft_strchr_idx(node->tokens[i][0].raw, '=') != (size_t)-1 &&
		ft_strchr_idx(node->tokens[i][0].raw, '=') != 0)
	{
		if (ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, '"') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, '\'') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, '\\') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, ' ') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, ' ') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, '$') ||
			(node->tokens[i][0].raw[0] != '_' && !ft_isalpha(node->tokens[i][0].raw[0])))
			break;
		i++;
	}
	if (i == node->token_count)
		return (-1);
	return (i);
}

void	xpnd_param_var(t_minishell *shell, t_astnode *node, char ***argv, size_t *n)
{
	size_t	i;
	size_t	i2;
	size_t	new_wc;
	char	**words;
	
	if (!argv && !*argv)
		return ;
	i = 0;
	new_wc = 0;
	while(i < *n + new_wc)
	{
		i2 = 0;
		words = expand_and_split(shell, node->tokens[i - new_wc][0].raw, 3);
		if (!words)
			_free_arr_perror_exit(shell, (void **)argv, "minishell: expand");
		while (words[i2])
		{
			ft_dirtyswap((void *)argv, ft_arradd_atindex((void **)*argv, words[i2], i + i2), free);
			i2++;
		}
		free(words);
		i += i2;
		new_wc += i2 - 1;
	}
	*n += new_wc;
}

void	word_splitting(t_minishell *shell, t_astnode *node, char ***argv, size_t *n)
{
	size_t	i;
	
	(void)node;
	if (!argv)
		return ;
	i = 0;
	while(i < *n)
	{
		if (!ft_dirtyswap((void **)(argv[0] + i), rem_quotes(argv[0][i]), free))
			_free_arr_perror_exit(shell, (void **)argv, "minishell: expand");
		i++;
	}
}

void	quote_removal(t_minishell *shell, t_astnode *node, char ***argv, size_t *n)
{
	size_t	i;
	
	(void)node;
	if (!argv)
		return ;
	i = 0;
	while(i < *n)
	{
		if (!ft_dirtyswap((void **)(argv[0] + i), rem_quotes(argv[0][i]), free))
			_free_arr_perror_exit(shell, (void **)argv, "minishell: expand");
		i++;
	}
}

typedef struct s_shell_expansion_fnc
{
	void	(*f)(t_minishell *shell, t_astnode *node, char ***argv, size_t *n);
}	t_shell_expansion_fnc;

static t_shell_expansion_fnc	*set_expansion_fncs(void)
{
	static t_shell_expansion_fnc shell_expansion_fnc[3] = {
		(t_shell_expansion_fnc){.f=xpnd_param_var},
		// (shell_expansion_fnc){.f= word_splitting},
		(t_shell_expansion_fnc){.f= quote_removal},
		(t_shell_expansion_fnc){.f= 0},	
	};
	return (shell_expansion_fnc);
}

char	**cmdv_prep(t_minishell *shell, t_astnode *node)
{
	char	**argv;
	t_shell_expansion_fnc *xpnsion_f;
	size_t	n;
	size_t	i;
	
	n = node->token_count;
	argv = ft_calloc(n + 1, sizeof(char **));
	if (!argv)
		return (NULL);
	xpnsion_f = set_expansion_fncs();
	node->cmd_i = get_cmd_idx(node);
	i = 0;
	while(xpnsion_f[i].f)
	{
		xpnsion_f[i].f(shell, node, &argv, &n);
		i++;
	}
	node->argc = n;
	return (argv);
}
