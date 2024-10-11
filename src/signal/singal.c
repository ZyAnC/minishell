/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:14:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/11 10:34:42 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Document's requirements:
	ctrl-C displays a new prompt on a new line.
	ctrl-D exits the shell.
	ctrl-\ does nothing.
*/

/*
	@What the function does?
	To listening SIGINT (ctrl-C) and SIGQUIT(ctrl-\).

	@action
	When receive SIGINT, we call handle_sigint();
	When receive SIGQUIT, we ignore it(SIG_IGN);
*/
void	init_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_heredoc(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
