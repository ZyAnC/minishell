/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_re.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:02:18 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/02 13:01:26 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	handle_in_re(t_cmd **cmd, t_list *tk_node)
{
	(*cmd) ->intype = TK_IN_RE;
	(*cmd) ->infile[(*cmd) ->ct_in++] = ((t_token *)((tk_node) ->content)) ->arg;
	(*cmd) ->inf = ((t_token *)((tk_node) ->content)) ->arg;
}

static void	handle_hdoc(t_cmd **cmd, t_list *tk_node)
{
	(*cmd) ->intype = TK_HDOC;
	(*cmd) ->limiter[(*cmd) ->ct_del] = ((t_token *)((tk_node) ->content)) ->arg;
	(*cmd) ->inf = NULL;
}

static void	handle_out_re(t_cmd **cmd, t_list *tk_node)
{
	(*cmd) ->outype = ((t_token *)(tk_node->content)) ->tk_type;
	(*cmd) ->outfile[(*cmd) ->ct_out] = ((t_token *)((tk_node) ->content)) ->arg;
	(*cmd) ->of = ((t_token *)((tk_node) ->content)) ->arg;
}

void	process_re(t_cmd **cmd, t_list *tk_node)
{
	t_token	*token;

	token = (t_token *)(tk_node->content);
	if (token->tk_type == TK_IN_RE)
		handle_in_re(cmd, tk_node);
	else if (token->tk_type == TK_HDOC)
		handle_hdoc(cmd, tk_node);
	else if (token->tk_type == TK_OUT_RE || token->tk_type == TK_APPEND)
		handle_out_re(cmd, tk_node);
}
