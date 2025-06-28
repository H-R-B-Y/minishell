/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:02:44 by cquinter          #+#    #+#             */
/*   Updated: 2025/06/27 17:02:22 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "./abstract_syntax_tree.h"
# include "./builtin.h"
# include <unistd.h>


void	execute_command(t_minishell *shell, char *path, char **argv, char**envp);
int		execute_ast(t_minishell *shell);
int		update_env(char ***envp, char *dup, char *name, ssize_t (f)(char **, char *));
int		set_n_envp(char ***envp, char **argv, size_t n);

#endif