/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:02:44 by cquinter          #+#    #+#             */
/*   Updated: 2025/07/02 21:27:35 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "./abstract_syntax_tree.h"
# include "./builtin.h"
# include <unistd.h>

# define EXEC_ALLCHILD 1
# define EXEC_DEFAULT 0



void	perror_exit(t_minishell *shell, char *message); // TODO: check if correct clean up everything and exit
void	_set_returncode(int *to_set, int code);

char	*get_exec_path(t_minishell *shell, char *cmd, char **envp);
char	**cmdv_prep(t_minishell *shell, t_astnode *node);

int		update_env(char ***envp, char *dup, char *name, ssize_t (f)(char **, char *));
int		set_n_envp(char ***envp, char **argv, size_t n);
int		set_any_env(t_minishell *shell);

int		execute_command(t_minishell *shell, t_astnode *node);
int		execute_pipe(t_minishell *shell, t_astnode *node);
int		execute_subshell(t_minishell *shell, t_astnode *node);
int		execute_seq(t_minishell *shell, t_astnode *node);
int		execute_logical(t_minishell *shell, t_astnode *node);

int		execute_ast(t_minishell *shell, t_astnode *node);

#endif