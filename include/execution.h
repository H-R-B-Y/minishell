/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:02:44 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/14 17:44:45 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "./abstract_syntax_tree.h"
# include "./builtin.h"
# include <unistd.h>

// TODO: Comment this header

char	*get_exec_path(t_minishell *shell, char *cmd, char **envp);
void	xpnd_param_var(t_minishell *shell, t_astnode *node,
			char ***argv, size_t *n);
void	filename_expansion(t_minishell *shell, t_astnode *node,
			char ***argv, size_t *n);
void	quote_removal(t_minishell *shell, t_astnode *node,
			char ***argv, size_t *n);
char	**cmdv_prep(t_minishell *shell, t_astnode *node);

typedef struct s_restore_rds
{
	int	subtype;
	int	to_fd;
	int	dupped1;
	int	dupped2;
}	t_restore_rds;

typedef struct s_shell_expansion_fnc
{
	void	(*f)(t_minishell *shell, t_astnode *node, char ***argv, size_t *n);
}	t_shell_expansion_fnc;

int		t_oflag(const int redr_type);
void	_close_rstore_fds(t_restore_rds *info);
int		init_rd_rstr_info(t_restore_rds **info, t_redirect_desc *desc);
int		rd_fd_restore(t_restore_rds *info);
void	rd_list_restore(t_list *info_lst);

int		update_env(char ***envp,
			char *dup, char *name, ssize_t (*f)(char **, const char *));
int		set_n_envp(char ***envp, char **argv, size_t n);
int		set_any_env(t_minishell *shell, char **argv, size_t n);
/**
 * @brief handles envp for both built ins and expernal commands
 * 
 * Sets '_' and cmd only environment variables.
 * 
 * @param shell the shell struct
 * @param node the current node
 * @param b_in a pointer to b_in. Checked to set envp accordingly
 * @return char* the env string from the environment
 */
void	set_cmd_envp(t_minishell *shell, t_astnode *node,
			t_builtincmd b_in);

void	get_exec_cmd(t_minishell *shell, t_astnode *node, t_builtincmd b_in);

int		execute_command(t_minishell *shell, t_astnode *node);
int		execute_pipe(t_minishell *shell, t_astnode *node);
int		execute_subshell(t_minishell *shell, t_astnode *node);
int		execute_seq(t_minishell *shell, t_astnode *node);
int		execute_logical(t_minishell *shell, t_astnode *node);
int		execute_ast(t_minishell *shell, t_astnode *node);

#endif