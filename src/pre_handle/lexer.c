/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:51:55 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/23 09:53:33 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

void		lexer(void);


/*
	This function will read the commands input by a user, and seperate token and
	words.
	test cases: (for case 2 and 3 , in our minishell will both consider them as wrong token)
	1. "echo "hello" >>> file.txt" -----> bash: syntax error near unexpected token `>'
	2. echo hello || echo dog  ----> hello
	3. echo hello ||| echo dog ----> bash: syntax error near unexpected token `|'
*/
void	lexer(void)
{
	int	i;
	int	j;

	i = 0;
	while (ms()->input[i])
	{
		j = 0;
		while (ms()->input[i] == ' ')
			j++;
		if (is_token(ms()->input[i])) // token are: |, <, >, <<, >>
			j = handle_token(i);
		else
			j = read_words(i);
		if (j < 0)
			return (0); // add_node failed.
		i += j;
	}
	return (1);
}

/*
	Before this function
*/
static bool	is_token(int i)
{
	if (ms()->input[i] == '|' && ms()->input[i] != '|')
}
