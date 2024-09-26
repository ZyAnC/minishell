/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:47:08 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/26 14:20:22 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

bool	is_pipe(t_token *token)
{
	if (!token)
		return (false);
	if (token->tk_type == TK_PIPE)
		return (true);
	return (false);
}

bool	is_dir(t_token *token)
{
	if (!token)
		return (false);
	if (token->tk_type == TK_IN_RE || token->tk_type == TK_OUT_RE
		|| token->tk_type == TK_HDOC || token->tk_type == TK_APPEND)
		return (true);
	return (false);
}

bool	is_dir_or_pipe(t_token *token)
{
	if (!token)
		return (false);
	if (is_pipe(token) || is_dir(token))
		return (true);
	return (false);
}
