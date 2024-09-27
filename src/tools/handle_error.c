/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:22:37 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/27 08:01:19 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	print_error(char *err_type, int err_fd)
{
	ft_putchar_fd(err_type, STDERR_FILENO);
	ms() ->exit = err_fd;
	return (false);
}

bool	stx_error(t_token *node)
{
	if (!node)
		print_error(NL_STX_ERR, 1);
	else if (node->tk_type == TK_PIPE)
		print_error(PIPE_STX_ERR, 1);
	else if (node->tk_type == TK_IN_RE)
		print_error(IN_RE_STX_ERR, 1);
	else if (node->tk_type == TK_OUT_RE)
		print_error(OUT_RE_STX_ERR, 1);
	else if (node->tk_type == TK_HDOC)
		print_error(HDOC_STX_ERR, 1);
	else if (node->tk_type == TK_APPEND)
		print_error(APED_STX_ERR, 1);
	return (false);
}
