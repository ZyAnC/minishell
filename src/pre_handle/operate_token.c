/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:28:56 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/02 09:58:41 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
	Generate a new node for lexer_list.
*/
t_token	*new_token(char *str, t_token_type tk_type)
{
	t_token	*node;

	node = ft_calloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
	node->str = str;
	node->tk_type = tk_type;
	node->idx++;
	return (node);
}

/*
	Add a new node to the lexer_list;
*/
int	add_token(char *str, t_token_type token)
{
	t_token	*node;

	if (!str)
		return (false);
	node = new_token(str, token);
	if (!node)
		return (-1);
	ft_lstadd_back(&ms() ->tokens, ft_lstnew(token));
	return (ft_strlen(str));
}

/*
	@Why I need this function?
	Becasue if I don't use it, then if I want to get the value of a t_token type data,
	I need write "((t_token *)(ms() ->tokens))->str", it is too looooooong.

	psn == RESET
		SET the tk_list to pointer to the head of list tokens;
	psn == NEXT
		MOVE the pointer to the next node;
	psn == CURRENT
		RETURN the content(t_token type) of the current node;
	psn == PREVIEW
		RETURN the content (t_token type) of the next node;
*/
t_token	*tk_list_manager(t_list_position psn)
{
	static t_list	*tk_list = NULL;

	if (psn == RESET)
		tk_list = ms() ->tokens;
	else if (psn == NEXT)
		tk_list = tk_list->next;
	else if (psn == CUR_CNT && tk_list)
		return (tk_list->content);
	else if (psn == NEXT_CNT && tk_list->next)
		return (tk_list->next->content);
	return (NULL);
}

/*
	@how to delete a node?
	 1. If the node is at the beginning:
	    You need to update the head of the list.
	 2. If the node is in the middle or at the end:
	    loop the list to find the node right before the delete_node, then update the list.
*/
void	del_node(t_list **list, t_list *node)
{
	t_list	*tmp;

	if (!list || !*list || !node)
		return ;
	tmp = *list;
	if (*list == node)
	{
		*list = (*list) ->next;
		free(((t_token *)(node->content)));
		free(tmp);
	}
	else
	{
		while (!(tmp->next) && (tmp->next) != node)
			tmp = tmp->next;
		tmp ->next = node ->next;
		free(((t_token *)(node->content)) ->str);
		free(node);
	}
}
