/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:05:21 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/23 09:50:11 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	@function
	Checking the passed list's token types.

	@return
		1: only contain TK_LOC_V;
		2: contain TK_LOC_V and TK_PIPE
		3: contain at least one other token type except TK_LOC_V and TK_PIPE;
		4: the list is empty;
*/
static int	checking_list_token_types(t_list *list)
{
	t_token	*token;
	bool	just_loc_v;

	just_loc_v = true;
	if (!list)
		return (4);
	while (list)
	{
		token = (t_token *)list->content;
		if (token->tk_type != TK_LOC_V && token->tk_type != TK_PIPE)
			return (3);
		if (token->tk_type == TK_PIPE)
			just_loc_v = false;
		list = list->next;
	}
	if (just_loc_v == true)
		return (1);
	else
		return (2);
}
/*
	@function
	While loop the token list, if found one TK_LOC_V type token is not valid defination variable,
	then return true. If every TK_LOC_V type token is valid defination, then return false.

	@return
	true: there is at least one invalid variable defination
	false: there is NO invalid variable defination
*/
static bool	is_there_invalid_defination(t_list *list)
{
	t_token	*token;

	if (!list)
		return (false);
//	printf("<---------------------is there invalid--1----------------->\n");// for testing!!!!!!!!!!!!!!!!
	while (list)
	{
		token = (t_token *)list->content;
//	printf("<---------------------is there invalid--2----------------->\n");// for testing!!!!!!!!!!!!!!!!
		if (token->tk_type == TK_LOC_V && is_defining_var(token->str) == false)
		{
			printf("<---------------------is there invalid--3----------------->\n");// for testing!!!!!!!!!!!!!!!!
			return (true);
		}
//		printf("<---------------------is there invalid--4----------------->\n");// for testing!!!!!!!!!!!!!!!!
		list = list->next;
	}
	return (false);
}
static void	del_beginning_locv(t_list **list)
{
	t_token	*current;
	t_list	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		current = (t_token *)((*list)->content);
		if (current->tk_type != TK_LOC_V && is_defining_var(current->str) == true)
			return ;
		tmp = (*list);
		(*list) = (*list)->next;
		del_node(tmp);
	}
}

static void	del_end_locv(t_list **list)
{
	t_list	*end_node;
	t_token	*token;

	if (!list || !(*list) || !(*list)->next)
		return ;
	while ((*list)->next && (*list)->next->next)
		(*list) = (*list)->next;
	token = ((t_token *)(*list)->next->content);
	if (token->tk_type == TK_LOC_V && is_defining_var(token->str) == true)
	{
		end_node = (*list)->next;
		(*list)->next = NULL;
		del_node(end_node);
	}
}

/*
	@function
	Delete the valid local variable defination in the token list. It is used when there is invalid
	local variable defination in the token list. In this case, we need to delete the valid ones.
	Need consider 3 conditions:
	1. node is at the beginning; // need to do this part
	2. node is at the middle of the list;
	3. node is at the end of the list. // need to do this part
	Thinking of pipe delete functions , to see if we can combine them together.
*/
static void	del_vaild_variable_define(t_list **list)
{
	t_token	*token;
	t_list	*delete;

	if (!list)
		return ;
	del_beginning_locv(list);
	while (list)
	{
		token = (t_token *)((*list)->next->content);
//	printf("<---------------------delete variable---1----------------->\n");// for testing!!!!!!!!!!!!!!!!!!
		if (token->tk_type == TK_LOC_V && is_defining_var(token->str) == true)
		{
			delete = (*list)->next;
//		printf("<---------------------delete variable---2----------------->\n");// for testing!!!!!!!!!!!!!!!!!!
			(*list)->next = delete->next;
			del_node(delete);
			continue ;
		}
//		printf("<---------------------delete variable---3----------------->\n");// for testing!!!!!!!!!!!!!!!!!!
		(*list) = (*list)->next;
	}
	del_end_locv(&ms()->tokens);
}

/*
	type:
		1: only contain TK_LOC_V;
		2: contain TK_LOC_V and TK_PIPE
		3: contain at least one other token type except TK_LOC_V and TK_PIPE;

	The different input cases and their actions:
	type=1	1: name=123 a=3				--> saving variables, don't go to execution
	type=1	2: name=23 1a=3				--> don't save any variable, delete "name=123", go to execution
	type=2	3: name=123 | a=3			--> don't save any variable, don't go to execution
	type=2	4: name=123 | 1a=3			--> don't save any variable, delete "name=123", go to execution
	type=3	5: name=123 | echo a		--> don't save any variable, delete "name=123", go to execution
	type=3	6: name=123 | 1name=123 | echo a	--> don't save any variable, delete "name=123", go to execution

	Why we delete valid defination in some conditions?
	Becasue it will simplify the exection part, in these conditions, these valid defination don't need to
	be exectued.

	Logic summary:
	1. As long there is an INVAILD variable defination in the input or the type = 3, then:
		- DON'T save any valid variable
		- Delete all the valid variable definations
		- Go to execution
	2. if type = 1, add variables to the local variable list, restart the minishell;
	3. if type = 2, restart the minishell
*/
bool	are_all_def_loc_var(void)
{
	t_list	*tmp;
	t_token	*token;
	int		type;

	type = checking_list_token_types(ms()->tokens);
//	printf("type=%d\n", type);// for testing!!!!!!!!!!!!!!!!!!
	if (is_there_invalid_defination(ms()->tokens) == true || type == 3)
	{
//		printf("<---------------are all def---------1----------------->\n");// for testing!!!!!!!!!!!!!!!!!!
		del_vaild_variable_define(&ms()->tokens);
		return (false);
	}
	if (type == 1)
	{
		tmp = ms()->tokens;
//		printf("<---------------are all def---------2----------------->\n");// for testing!!!!!!!!!!!!!!!!!!
		while (tmp)
		{
			token = (t_token *)(tmp->content);
			add_node_to_list(&(ms()->local_var), token->str);
			tmp = tmp->next;
		}
		return (true);
	}
//	printf("<---------------are all def---------3----------------->\n");// for testing!!!!!!!!!!!!!!!!!!
	if (type == 2 || type == 3)
		delete_extra_pipes(&ms()->tokens);
//	printf("<---------------are all def---------4----------------->\n");// for testing!!!!!!!!!!!!!!!!!!
	return (true);
}
