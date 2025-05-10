/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/10 13:00:16 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
I want to rewrite the lexar to better handle inputs

currently there is a small issue with the way we handle errors

when a tokenisation error is happening, we delete the token list, 
then we continue to read lines until we get a valid token list, meaning we re-parse
and re-parse and re-parse again and again until we find a correct list.

this is not good at all, I want to be able to store the state of the tokeniser
and return errors DURING the parsing process so that they can be handled on the
fly.

This means we need to keep track of what is currently being parsed?

I think we might need a stack to store start/end tokens: 
when we encounter a bracket we push to the stack, then we keep parsing until we reach
the end, if there was no close bracket then the error is whatever is on top of the stack?
so quotes and bracket errors are caught here instead of being tested for afterwards?


*/
t_list	*tokensise(char *str)
{
	
}
