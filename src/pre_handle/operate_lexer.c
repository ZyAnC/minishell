/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:28:56 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/24 11:42:47 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_lexer	*new_lexer(char *str, t_token_type token);
int		add_lexer(char *str, t_token_type token);
void	lexer_addback(t_lexer *node);

t_lexer	*new_lexer(char *str, t_token_type token)
{
	t_lexer	*node;
	static int	index = 0;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->str = str;
	node->token = token;
	node->index = index++;
	node->next = NULL;
	node->pre = NULL;
	return (node);
}

int	add_lexer(char *str, t_token_type token)
{
	t_lexer	*node;

	node = new_lexer(str, token);
	if (!node)
		return (0);
	lexer_addback(node);
	return (1);
}

void	lexer_addback(t_lexer *node)
{
	t_lexer *tmp;

	?????????
}
