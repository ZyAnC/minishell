/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:21:42 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/09 12:07:09 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The function will count the amount of <, >, >> and <<.
*/
void	count(t_cmd **cmd, t_list *tk_lt, int start, int end)
{
	t_token	*token;

	while (tk_lt)
	{
		token = tk_lt->content;
		if (token->idx >= start && token->idx <= end)
		{
			if (token->tk_type == TK_IN_RE)
				(*cmd) ->ifnum++;
			else if (token->tk_type == TK_OUT_RE || token->tk_type == TK_APPEND)
				(*cmd) ->ofnum++;
			else if (token->tk_type == TK_HDOC)
				(*cmd) ->herenum++;
			else if (token->tk_type == TK_WORD || token->tk_type == TK_DOUBLE_QT
				|| token->tk_type == TK_SINGLE_QT)
				(*cmd) ->word++;
		}
		if (token->idx > end)
			break ;
		tk_lt = tk_lt->next;
	}
}
/*
	Allocate memory for cmd, infile, outfile, limiter dyadic array.
*/
bool	allocate_mem(t_cmd **cmd)
{
	(*cmd) ->infile = ft_calloc(((*cmd) ->ifnum + 1), sizeof(char *));
	if (!(*cmd) ->infile)
		return (false);
	(*cmd) ->outfile = ft_calloc(((*cmd) ->ofnum + 1), sizeof(char *));
	if (!(*cmd) ->outfile)
		return (false);
	(*cmd) ->cmd = ft_calloc(((*cmd) ->word + 1), sizeof(char *));
	if (!(*cmd) ->cmd)
		return (false);
	(*cmd) ->limiter = ft_calloc(((*cmd) ->herenum + 1), sizeof(char *));
	if (!(*cmd) ->limiter)
		return (false);
	return (true);
}
