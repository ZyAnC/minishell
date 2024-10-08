/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:02:58 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/08 12:09:12 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_error(char *message)
{
	if (!access(message, F_OK))
		ex_error(message, PREMISSON, 126);
	else
		ex_error(message,NFILE,2);
	restart(0);
}

void	ex_error(char *message, t_err_type type, int err_status)
{
	ft_putstr_fd("minishell: ", 2);
	if(message)
		ft_putstr_fd(message, 2);
	if (type == DIRECTORY)
		ft_putstr_fd(": Is a directory", 2);
	else if (type == COMMAND)
		ft_putstr_fd(": command not found", 2);
	else if  (type == NFILE)
		ft_putstr_fd(": No such file or directory", 2);
	else if  (type == PREMISSON)
		ft_putstr_fd("Permission denied", 2);
	else if  (type == FORK)
		ft_putstr_fd("fork failed", 2);
	else if  (type == PIPE)
		ft_putstr_fd("pipe failed", 2);
	else if  (type == ERR)
		ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	ms()->exit = err_status;
}

bool	print_error(char *err_type, int err_fd)
{
	ft_putstr_fd(err_type, STDERR_FILENO);
	write(2, "\n", 1);
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
