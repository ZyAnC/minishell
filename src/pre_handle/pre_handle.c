/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:48:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/08 12:51:50 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge(t_list *list)// add static after testing!!!!!!!!!!
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
		next = list->next->content;
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
bool	are_all_def_var(void)// add static after testing !!!!!!!!!
{
	t_list	*tmp;
	t_token	*token;

	tmp = ms()->tokens;
	while (tmp)
	{
		token = (t_token *)(tmp->content);
		if (!ft_strchr(token->str, '='))
			return (false);
		if (!is_defining_var(tmp ->content))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

void	restruct_token(void)
{
	t_list	*tmp;
	t_token	*cur_tk;
	t_token	*next_tk;
	t_list	*delete;

	tmp = ms()->tokens;
	while (tmp)
	{
		cur_tk = (t_token *)(tmp->content);
		if (!tmp->next)
			break ;
		next_tk = ((t_token *)((tmp->next)->content));
		if (is_dir(cur_tk))
		{
			cur_tk->arg = ft_strdup(next_tk->str);
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
	if (!parsing())
		return (false);
	if (are_all_def_var())
		return (false);
	return (true);
}
