/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_lexer_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:28:56 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/25 13:08:54 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
	Generate a new node for lexer_list.
*/
t_lexer	*new_lexer(char *str, t_token_type token)
{
	t_lexer	*node;
	static int	index = 0;

	node = ft_calloc(1, sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->str = str;
	node->token = token;
	node->index = index++;
	node->next = NULL;
	node->pre = NULL;
	return (node);
}

/*
	Add a new node to the back of the lexer_list.
*/
void	lexer_addback(t_lexer *node)
{
	t_lexer *tmp;

	if (ms() ->lexer_list == NULL)
	{
		ms() ->lexer_list == node;
		return ;
	}
	tmp = ms() ->lexer_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->pre = tmp;
}

/*
	Add a new node to the lexer_list;
*/
bool	add_lexer(char *str, t_token_type token)
{
	t_lexer	*node;

	if (!str)
		return (false);
	node = new_lexer(str, token);
	if (!node)
		return (false);
	lexer_addback(node);
	return (true);
}


