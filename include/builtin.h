/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:31:46 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/24 15:48:40 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define BLTINCOUNT 8

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_minishell	t_minishell;

/**
 * @brief typedef for all builtins
 */
typedef int (*t_builtincmd)(t_minishell *, char **, char ***);

/**
 * @brief Internal struct for mapping strings to builtins
 * @param match The string to match
 * @param fnc The function it pertains too
 */
struct s_buitinmapping
{
	/// @brief The string to match
	char			*match;
	/// @brief The function it pertains too
	t_builtincmd	fnc;
};

/*
Follows are prototypes for the builtin commandss
*/

/**
 * @brief change the current working directory
 * 
 * @param shell the shell struct
 * @param argv the arguments passed to cd
 * @param envp the current environment variables
 * @return int the statuscode
 */
int	builtin_cd(t_minishell *shell, char **argv, char ***envp);

/**
 * @brief echo some text
 * 
 * @param shell the shell struct
 * @param argv the arguments passed to cd
 * @param envp the current environment variables
 * @return int the statuscode
 */
int	builtin_echo(t_minishell *shell, char **argv, char ***envp);

/*
 * @brief print all environment variables set
 * 
 * @param shell the shell struct
 * @param argv the arguments passed to the command
 * @param envp the current environment variables
 * @return int 
 */
int	builtin_env(t_minishell *shell, char **argv, char ***envp);

/**
 * @brief exit the shell
 * 
 * @param shell the shell struct
 * @param argv the arguments passed to the command
 * @param envp the current environment variables
 * @return int the status code (ignored in this case)
 */
int	builtin_exit(t_minishell *shell, char **argv, char ***envp);

/**
 * @brief add a new variable to the environment
 * 
 * @param shell the shell struct
 * @param argv the arguments passed to the function
 * @param envp the current environment variables
 * @return int the return code
 */
int	builtin_export(t_minishell *shell, char **argv, char ***envp);

/**
 * @brief print current working directory
 * 
 * @param shell the shell struct
 * @param argv the arguements passed to the command
 * @param envp the current environment variables
 * @return int the return code
 */
int	builtin_pwd(t_minishell *shell, char **argv, char ***envp);

/**
 * @brief remove a variable from the environment
 * 
 * @param shell the shell struct
 * @param argv the arguements passed to the command
 * @param envp the current environment variables
 * @return int the status code
 */
int	builtin_unset(t_minishell *shell, char **argv, char ***envp);

/**
 * @brief its a secret
 * 
 * @param shell the shell struct
 * @param argv the arguements passed to the command
 * @param envp the current environment variables
 * @returns 0
 */
int	builtin_(t_minishell *shell, char **argv, char ***envp);

#endif