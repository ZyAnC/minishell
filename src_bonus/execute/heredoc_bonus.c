/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:59:12 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/11 13:53:34 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	restart2(void)
{
	if (ms()->prompt)
		free(ms()->prompt);
	if (ms()->input)
		free(ms()->input);
	ms()->fd[0] = -1;
	ms()->fd[1] = -1;
	ms()->in_fd = STDIN_FILENO;
	ms()->out_fd = STDOUT_FILENO;
	ft_lstclear((&ms()->tokens), (void (*)(void *))delete_token);
	free_cmd_list();
	ms()->hstatus = 1;
}

static void	hdoc_parents(t_cmd *cm, int pipefd[2], pid_t pid)
{
	close(pipefd[1]);
	signal_ignore();
	get_status(pid);
	read(pipefd[0], &ms()->heredoc_count, sizeof(ms()->heredoc_count));
	read(pipefd[0], &ms()->limiter_count, sizeof(ms()->limiter_count));
	close(pipefd[0]);
	if (cm->intype == TK_HDOC)
	{
		if (ms()->exit != 130)
			cm->intype = TK_IN_RE;
		if (cm->inf)
			free(cm->inf);
		cm->inf = ft_strdup("here_doc");
		if (!cm->ifnum)
			ms()->cmds->ifnum++;
		set_fd(cm);
	}
	if (ms()->exit == 130)
		restart2();
	signal_default();
}

pid_t	type_hdoc(t_cmd *cm)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		ex_error("Pipe", PIPE, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		heredoc(cm);
		close(pipefd[0]);
		write(pipefd[1], &ms()->heredoc_count, sizeof(ms()->heredoc_count));
		write(pipefd[1], &ms()->limiter_count, sizeof(ms()->limiter_count));
		close(pipefd[1]);
		exit(0);
	}
	hdoc_parents(cm, pipefd, pid);
	return (pid);
}
