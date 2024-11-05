/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:14:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/11/05 20:51:57 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_default(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (ms()->heredoc_count == -1)
	{
		printf("minishell: warning: here-document at ");
		printf("line %d delimited", ms()->lines);
		printf(" by end-of-file (wanted `%s')\n",
			ms()->cmds->limiter[--ms()->limiter_count]);
		ms()->heredoc_count = 0;
	}
}

void	signal_heredoc(void)
{
	printf("haaaahh\n");
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_heredoc);
}

void	signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
