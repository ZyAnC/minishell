/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_extra_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:46:11 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/23 14:28:13 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	@function
	Work with function delete_extra_pipes(), to delete extra pipes in the token list after local variable
	checking. This function is just delete the pipes which are at the beiginning of the list.
*/
static void	del_beginning_pipes(t_list **list)
{
	t_token	*current;
	t_list	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		current = (t_token *)((*list)->content);
		if (current->tk_type == TK_PIPE)
		{
			tmp = (*list);
			(*list) = (*list)->next;
			del_node(tmp);
		}
		else
			return ;
	}
}

static void	delete_end_pipe(t_list *list)
{
	t_list *end_node;

	if (!list || !list->next)
		return ;
	while (list && list->next && list->next->next)
		list = list->next;
	if (((t_token *)list->next->content)->tk_type == TK_PIPE)
	{
		end_node = list->next;
		list->next = NULL;
		del_node(end_node);
	}
}

/*
	@function
	After checking the local variables, in some conditions, the valid variable definations will be deleted.
	Then it might leave extra pipe token in the list, so we need to delete these extra pipes
	The node might be in three places:
	1. at the beginnings;
	2. in the middle;
	3. at the end;
*/
void	delete_extra_pipes(t_list **list)
{
	t_token	*current;
	t_token	*next;
	t_list	*tmp;
	t_list	*newlist;

	if (!list)
		return ;
	del_beginning_pipes(list);
	newlist = *list;
	while (newlist)
	{
		current = (t_token *)(newlist->content);
		if (newlist->next)
		{
			next = (t_token *)(newlist->next->content);
			if (current->tk_type == TK_PIPE && next->tk_type == TK_PIPE)
			{
				tmp = newlist->next;
				newlist->next = tmp->next;
				del_node(tmp);
				continue ;
			}
		}
		newlist = newlist->next;
	}
	delete_end_pipe(*list);
}
