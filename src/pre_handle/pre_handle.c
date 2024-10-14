/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:48:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/14 10:38:11 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	merge(t_list *list)
{
	t_token	*cur;
	t_token	*next;
	char	*tmp;
	t_list	*delete;
	while (list)
	{
		cur = list->content;
		if (!(list->next))
			return ;
		if (!cur->merge)
		{
			list = list->next;
			continue ;
		}
		next = (list->next)->content;
		tmp = cur->str;
		cur->str = ft_strjoin(cur->str, next->str);
		free(tmp);
		if (!next->merge)
			cur->merge = next->merge;
		delete = list->next;
		list->next = list->next->next;
		del_node(delete);
	}
}

/*
	This funtion will loop the token list, to check if the input just
	contains defining environment variable, such as the input is
	"name=sherry | export shcool="Hive Helsinki"
*/
static bool	are_all_def_var(void)
{
	t_list	*tmp;
	t_token	*token;

	tmp = ms()->tokens;
	while (tmp)
	{
		token = (t_token *)(tmp->content);
		if (!ft_strchr(token->str, '='))
			return (false);
		if (!is_defining_var(token->str))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

static void	restruct_token(void)
{
	t_list	*tmp;
	t_token	*cur_tk;
	t_list	*delete;

	tmp = ms()->tokens;
	while (tmp)
	{
		cur_tk = (t_token *)(tmp->content);
		if (!tmp->next)
			break ;
		if (is_dir(cur_tk))
		{
			cur_tk->arg = ft_strdup(((t_token *)((tmp->next)->content))->str);
			delete = tmp->next;
			if (!(tmp->next)->next)
			{
				tmp->next = NULL;
				break ;
			}
			tmp->next = (tmp->next)->next;
			del_node(delete);
		}
		tmp = tmp->next;
	}
}


static void	assign_token_index(void)
{
	t_list	*list;
	t_token	*token;
	int		i;

	list = ms()->tokens;
	i = 0;
	while (list)
	{
		token = (t_token *)(list->content);
		token->idx = i++;
		list = list->next;
	}
}


bool	pre_handle(void)
{
	if (!check_quote())
		return (false);
	if (!lexer())
		return (print_error(ADD_TOKEN_FAILED, 1));
	if (!check_syntax())
		return (false);
	restruct_token();
	expander();
	merge(ms() ->tokens);
	assign_token_index();
	if (are_all_def_var())
		return (false);
	if (!parsing())
		return (false);
//print_list(ms()->tokens, 1);//for testing !!!!!!!!!!!!!!!!!!!!!
//print_cmd();//for testing !!!!!!!!!!!!!!!!!!!!!
	return (true);
}
