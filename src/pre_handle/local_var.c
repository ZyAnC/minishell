/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:05:21 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/21 14:38:21 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The syntax of defining  enviroment varible: name=value
	Rule:
	1. there is no space between "name", "=" and "value", like
	   name =123, name= 123 are all wrong;
	2. the variable name only start with either letter or '_', and only
	   contains letter, '_' and number.
	   like 2name=123, *name=123, na$me=123 are all wrong;

	f_equal: when loop the str, if encounter a "=" then f_equal=true;
	f_alp_uds: when loop the str, if encounter a alphabeta or "_", then
				f_alp_uds=true;
*/
bool	is_defining_var(char *str)
{
	int		i;
	bool	f_equal;
	bool	f_alp_uds;

	i = -1;
	f_equal = false;
	f_alp_uds = false;
	while (str[++i])
	{
		if (str[i] == '=')
			f_equal = true;
		else if (str[i] == '_' || ft_isalpha(str[i]))
			f_alp_uds = true;
		else if (!ft_isalpha(str[i]) && str[i] != '_'
			&& !f_equal && !f_alp_uds)// the name start with non-alpha, non-'_', is illegal.
			return (false);
		else if (!ft_isalnum(str[i]) && str[i] != '_'
			&& !f_equal)// there is illegal character in the name.
			return (false);
	}
	if (f_equal == false)
		return (false);
//	add_node_to_list(&(ms()->local_var), str);
	return (true);
}
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

// static void	delete_loc_var_node(void)
// {
// 	t_list	*tmp;
// 	t_token	*token;

// 	tmp = ms()->tokens;
// 		while (tmp)
// 		{
// 			token = (t_token *)(tmp->content);
// 			if (token->tk_type == TK_LOC_V)
// 				delete_token(token);
// 			tmp = tmp->next;
// 		}
// 		tmp = ms()->tokens;
// 		while (tmp)
// 		{
// 			token = (t_token *)(tmp->content);
// 			if (token->tk_type == TK_PIPE)
// 				delete_token(token);
// 			else
// 				break ;
// 			tmp = tmp->next;
// 		}
// }

/*
	This funtion will loop the token list, to check if the input just
	contains defining environment variable, there are three different
	action based on the input.
	1: name=123 a=3
	2: name=123 | a=3
	3: name=123 | echo a

	the corresponding action is:
	1: saving the variable into local variable list, don't go to execution;
	2: do nothing, don't go to the execution;
	3: just execution "echo a" part; but now we didn't consider this contation.

	type:
		1: only contain TK_LOC_V;
		2: contain TK_LOC_V and TK_PIPE
		3: contain at least one other token type except TK_LOC_V and TK_PIPE;
*/
bool	are_all_def_loc_var(void)
{
	t_list	*tmp;
	t_token	*token;
	int		type;

	type = checking_list_token_types(ms()->tokens);
	if (type == 2)
		return (true);
	if (type == 3)
	{
//		delete_loc_var_node();
		return (false);
	}
	if (type == 1)
	{
		tmp = ms()->tokens;
		while (tmp)
		{
			token = (t_token *)(tmp->content);
			add_node_to_list(&(ms()->local_var), token->str);
			tmp = tmp->next;
		}
	}
	return (true);
}
