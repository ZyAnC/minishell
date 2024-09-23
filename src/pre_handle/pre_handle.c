/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:48:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/23 13:35:25 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

bool		pre_handle(void);
static bool	lexer(void);
static int	read_token(int i);

bool	pre_handle(void)
{
	if (!check_quote()) // it will check if the input is quoted correctly
		return (false);
	if (!lexer())
		return (false);
	if (!check_synatx())
		return (false);
	expander();
	if (!parser())
		return (false);
	if (check_all_local()) // what's this for?????
		return (false);
	return (true);
}

/*
	This function will read the input and seperate it into token and words.

*/
static bool	lexer(void)
{
	int	i;
	int	j;

	i = 0;
	while (ms()->input[i])
	{
		j = 0;
		while (ms()->input[i] == ' ') // here conside the seperator is only by space.
			j++;
		if ((ms()->input[i]) == '|' || ms()->input[i] == '<'
			|| ms()->input[i] == '>') // token are: |, <, >, <<, >>
			j = read_token(i);
		else
			j = read_words(i);
		if (j < 0)
			return (false); // add_node failed.
		i += j;
	}
	return (true);
}

/*
	This function will process following cases as:
	1.	input: ... || ...
		token: 2 tokens '|' and '|';
	2.	input: ... >>> ...
		token: 2 tokens '>>' and '<';
	and so on and so forth.

	test cases: (for case 2 and 3 , in our minishell will both consider them as wrong token)
	1. "echo "hello" >>> file.txt" -----> bash: syntax error near unexpected token `>'
	3. echo hello ||| echo dog ----> bash: syntax error near unexpected token `|'
*/
static int	read_token(int i)
{
	int	j;

	j = 0;
	if (ms()->input[i] == '|')
		j = add_token(ft_strdup("|"), TK_PIPE, false);
	else if (!ft_strncmp(&(ms()->input[i]), "<<", 2))
		j = add_token(ft_strdup("<<"), TK_HDOC, false);
	else if (!ft_strncmp(&(ms()->input[i]), ">>", 2))
		j =  add_token(ft_strdup(">>"), TK_APPEND, false);
	else if (ms()->input[i] == '<')
		j = add_token(ft_strdup("<"), TK_IN_RE, false);
	else
		j = add_token(ft_strdup(">"), TK_OUT_RE, false);
	return (j);
}
