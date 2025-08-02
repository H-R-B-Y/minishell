/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:02:44 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/02 18:34:13 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "./abstract_syntax_tree.h"
# include "./builtin.h"
# include <unistd.h>

// TODO: Comment this header

char	*get_exec_path(t_minishell *shell, char *cmd, char **envp);
char	**cmdv_prep(t_minishell *shell, t_astnode *node);

int		update_env(char ***envp,
			char *dup, char *name, ssize_t (*f)(char **, const char *));
int		set_n_envp(char ***envp, char **argv, size_t n);
int		set_any_env(t_minishell *shell, char **argv, size_t n);

int		execute_command(t_minishell *shell, t_astnode *node);
int		execute_pipe(t_minishell *shell, t_astnode *node);
int		execute_subshell(t_minishell *shell, t_astnode *node);
int		execute_seq(t_minishell *shell, t_astnode *node);
int		execute_logical(t_minishell *shell, t_astnode *node);
int		execute_ast(t_minishell *shell, t_astnode *node);

#endif