/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:24:17 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/30 14:31:01 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	count_in_out_dir(t_cmd **cmd, t_list *tk_lt, int start, int end)
{
	t_token	*token;

	while (tk_lt)
	{
		token = tk_lt->content;
		if (token->idx >= start && token->idx <= end)
		{
			if (token->tk_type == TK_IN_RE)
				(*cmd) ->ifnum++;
			else if (token->tk_type == TK_OUT_RE)
				(*cmd) ->ofnum++;
		}
		tk_lt = tk_lt->next;
	}
}
/*
	Allocate memory for infile an outfile in each command node.
*/
static void	allocate_mem(t_cmd **cmd)
{
	(*cmd) ->infile = ft_calloc(((*cmd) ->ofnum + 1), sizeof(char *)); //
	if (!(*cmd) ->infile)
		return ;
	(*cmd) ->outfile = ft_calloc(((*cmd) ->ofnum + 1), sizeof(char *));
	if (!(*cmd) ->outfile)
		return ;
}

static t_cmd	*new_cmd(int start, int end)
{
	t_list	*tmp;
	t_token	*token;
	t_cmd	*cmd_nd;

	allocate_mem(&cmd_nd);
	tmp = ms() ->tokens;
	cmd_nd = ft_calloc(1, sizeof(t_cmd));
	count_in_out_dir(&cmd_nd, tmp, start, end); // implement the function
	while (tmp)
	{
		token = tmp->content;
		if (token->idx >= start && token->idx <= end)
		{
			if (token->tk_type)
			if (token->tk_type == TK_IN_RE)
			{
				cmd_nd->intype = TK_IN_RE;
			}
			else if (token->tk_type == TK_WORD)
				cmd_nd->cmd = ft_split(token->str, ' ');


		}
		tmp = tmp->next;
	}
	cmd_nd->prepipe = 0;
	cmd_nd->next = NULL;
}
/*
	This function will group tokens seperated by '|', then add them into cmd_list;
*/
bool	parsing(void)
{
	t_list	*tmp;
	t_token	*token;
	int		i;

	if (!ms() ->tokens)
		return (true);
	i = 0;
	tmp = ms() ->tokens;
	while (tmp)
	{
		token = tmp->content;
		if (token->tk_type == TK_PIPE)
		{
			add_cmd(new_cmd((i + 1), token->idx)); // token's index start from 1, right????
			i = token->idx;
		}
		tmp = tmp->next;
	}
	add_cmd(new_cmd((i + 1),
		((t_token *)((ft_lstlast(ms() ->tokens)) ->content)) ->idx)); // the last command part.
}
