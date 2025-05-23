/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:31:46 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/23 14:08:52 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define BLTINCOUNT 8

# include <stdlib.h>

typedef struct s_minishell	t_minishell;

/**
 * @brief typedef for the builtin command definitions
 * 
 * @note
 * builtin functions should not be run under a fork because they need 
 * access to the current state of the shell, this can be proven by running
 * the following:
 * 
 * ```bash
 * export TESTLOL=3 & sleep 2 && echo $TESTLOL
 * ```
 * or
 * ```bash
 * export TESTLOL=2 &
 * env | grep TEST
 * ```
 * 
 * @param shell the shell struct
 * @param argv the arguments passed to the function
 * @param envp the current environment variables
 * @return int the statuscode
 */
typedef int (*t_builtincmd)(t_minishell *shell, char **argv, char **envp);

/*
I will add some utility functions here for checking if 
a command is a builtin
*/

struct s_buitinmapping {
	char			*match;
	t_builtincmd	fnc;
};

/**
 * @brief Get the builtincmd object for a given string
 * 
 * @param str the string to check for a builtin command
 * @return t_builtincmd function pointer to the command or NULL
 */
t_builtincmd	get_builtincmd(char *str);

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
int	builtin_cd(t_minishell *shell, char **argv, char **envp);

/**
 * @brief echo some text
 * 
 * @param shell the shell struct
 * @param argv the arguments passed to cd
 * @param envp the current environment variables
 * @return int the statuscode
 */
int	builtin_echo(t_minishell *shell, char **argv, char **envp);

/*
 * @brief print all environment variables set
 * 
 * @param shell the shell struct
 * @param argv the arguments passed to the command
 * @param envp the current environment variables
 * @return int 
 */
int	builtin_env(t_minishell *shell, char **argv, char **envp);

/**
 * @brief exit the shell
 * 
 * @param shell the shell struct
 * @param argv the arguments passed to the command
 * @param envp the current environment variables
 * @return int the status code (ignored in this case)
 */
int	builtin_exit(t_minishell *shell, char **argv, char **envp);

/**
 * @brief add a new variable to the environment
 * 
 * @param shell the shell struct
 * @param argv the arguments passed to the function
 * @param envp the current environment variables
 * @return int the return code
 */
int	builtin_export(t_minishell *shell, char **argv, char **envp);

/**
 * @brief print current working directory
 * 
 * @param shell the shell struct
 * @param argv the arguements passed to the command
 * @param envp the current environment variables
 * @return int the return code
 */
int	builtin_pwd(t_minishell *shell, char **argv, char **envp);

/**
 * @brief remove a variable from the environment
 * 
 * @param shell the shell struct
 * @param argv the arguements passed to the command
 * @param envp the current environment variables
 * @return int the status code
 */
int	builtin_unset(t_minishell *shell, char **argv, char **envp);

#endif