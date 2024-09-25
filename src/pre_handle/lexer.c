/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:02:38 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/25 10:41:06 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
	This function is for read the whole quote words, like "hello",
	'abcdef'.

	Parameters:
	i:	the start position;
	quote: " or ';
*/
static int	handle_quotes(int i, char quote)
{
	int	j;

	j = 0;
	if (ms() ->input[i + j] == quote)
	{
		j++;
		while (ms() ->input[i + j] && ms() ->input[i + j] != quote)
			j++;
		j++; // now ms() ->input[i + j] is the character after the second quote.
	}
	return (j);
}

static bool	is_token(i)
{
	if((ms() ->input[i]) == '|' || ms() ->input[i] == '<'
			|| ms() ->input[i] == '>')
		return (true);
	return (false);
}

/*
	How to read a word?
	1. current character is not NULL, is not a token;
	2. get quotes part "...."'....'"...";
	3.
*/
static int	read_words(int i)
{
	int	j;

	j = 0;
	while (ms() ->input[i + j] && !is_token(ms() ->input[i + j]))
	{
		j += handle_quotes((i + j), '\"');
		j += handle_quotes((i + j), '\'');
		if (ms() ->input[i + j] == ' ')
			break ;
		j++;
	}
	if (!add_lexer(ft_substr(ms() ->input, i , j), TK_NONE))
		return (-1);
	return (j);
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
		j = add_lexer(ft_strdup("|"), TK_PIPE);
	else if (!ft_strncmp(&(ms()->input[i]), "<<", 2))
		j = add_lexer(ft_strdup("<<"), TK_HDOC);
	else if (!ft_strncmp(&(ms()->input[i]), ">>", 2))
		j =  add_lexer(ft_strdup(">>"), TK_APPEND);
	else if (ms() ->input[i] == '<')
		j = add_lexer(ft_strdup("<"), TK_IN_RE);
	else if (ms() ->input[i] == '>')
		j = add_lexer(ft_strdup(">"), TK_OUT_RE);
	return (j);
}
/*
	This function will read the input and seperate it into token and words.
	Note:
		1. we just conside the seperator is only space.
		2. token are : |, <, >, <<, >>;
*/
bool	lexer(void)
{
	int	i;
	int	j;

	i = 0;
	while (ms() ->input[i])
	{
		j = 0;
		while (ms() ->input[i] == ' ')
			j++;
		if (is_token(ms() ->input[i]))
			j = read_token(i);
		else
			j = read_words(i);
		if (j < 0)
			return (false);
		i += j;
	}
	return (true);
}

