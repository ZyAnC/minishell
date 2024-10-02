/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:24:17 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/02 12:59:13 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static t_cmd	*new_cmd(int start, int end)
{
	t_list	*tmp;
	t_token	*token;
	t_cmd	*cmd_nd;

	tmp = ms() ->tokens;
	cmd_nd = ft_calloc(1, sizeof(t_cmd));
	count(&cmd_nd, tmp, start, end);
	if (!allocate_mem(&cmd_nd))
		return (ft_strdup(""));
	while (tmp)
	{
		token = tmp->content;
		if (token->idx >= start && token->idx <= end)
		{
			if (is_dir(token->tk_type))
				process_re(&cmd_nd, tmp); // index how to increase?????
			else if (token->tk_type == TK_WORD)
				cmd_nd->cmd[cmd_nd->ct_w] = token->str;
		}
		tmp = tmp->next;
	}
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
		if (token->tk_type == TK_PIPE && tmp->next)
		{
			add_cmd(new_cmd((i + 1), token->idx)); // token's index start from 1, right????
			i = token->idx;
		}
		if (!tmp->next)
			add_cmd(new_cmd((i + 1), ((t_token *)tmp->content) ->idx));
		tmp = tmp->next;
	}
}
