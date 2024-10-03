/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:02:38 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/03 11:07:52 by jingwu           ###   ########.fr       */
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
// static int	handle_quotes(int i, char quote)
// {
// 	int	j;

// 	j = 0;
// 	if (ms() ->input[i + j] == quote)
// 	{
// 		j++;
// 		while (ms() ->input[i + j] && ms() ->input[i + j] != quote)
// 			j++;
// 		j++; // now ms() ->input[i + j] is the character after the second quote.
// 	}
// 	return (j);
// }
/*
	In this program, the meta_characters are: |, <, >, <<, >>.
*/
static bool	is_meta_char(int i)
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
// static int	read_words(int i)
// {
// 	int	j;

// 	j = 0;
// 	while (ms() ->input[i + j] && !is_meta_char(ms() ->input[i + j]))
// 	{
// 		j += handle_quotes((i + j), '\"');
// 		j += handle_quotes((i + j), '\'');
// 		if (ms() ->input[i + j] == ' ')
// 			break ;
// 		j++;
// 	}
// 	if (!add_token(ft_substr(ms() ->input, i , j), TK_WORD))
// 		return (-1);
// 	return (j);
// }

static int	find_match(char *matcher, char *str)
{
	int		i;
	char	*word;
	bool	merge;

	i = 0;
	while (str[i] && !ft_strchr(matcher, str[i]))
		i++;
	merge = check_mergerable(matcher, str, i);
	word = ft_substr(str, 0, i);
	if (matcher[0] = '"')
		add_token(word, TK_DOUBLE_QT, merge);
	else if (matcher[0] = '\'')
		add_token(word, TK_SINGLE_QT, merge);
	else
		add_token(word, TK_WORD, merge);
	return (i);
}

static int	read_word(int i)
{
	int	j;

	j = 0;
	if (ms() ->input[i] == '"')
		j = find_match("\"", &ms() ->input[i + 1]) + 2;
	else if (ms() ->input[i] == '\'')
		j = find_match("'", &ms() ->input[i + 1]) + 2;
	else
		j = find_match("<>'\"|", &ms() ->input[i]);
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
static int	read_meta_char(int i)
{
	int	j;

	j = 0;
	if (ms()->input[i] == '|')
		j = add_token(ft_strdup("|"), TK_PIPE, false);
	else if (!ft_strncmp(&(ms()->input[i]), "<<", 2))
		j = add_token(ft_strdup("<<"), TK_HDOC, false);
	else if (!ft_strncmp(&(ms()->input[i]), ">>", 2))
		j =  add_token(ft_strdup(">>"), TK_APPEND, false);
	else if (ms() ->input[i] == '<')
		j = add_token(ft_strdup("<"), TK_IN_RE, false);
	else if (ms() ->input[i] == '>')
		j = add_token(ft_strdup(">"), TK_OUT_RE, false);
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
		if (is_meta_char(ms() ->input[i]))
			j = read_meta_char(i);
		else
			j = read_words(i);
		if (j < 0)
			return (false);
		i += j;
	}
	return (true);
}

