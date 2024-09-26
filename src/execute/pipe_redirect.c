/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:49:16 by yzheng            #+#    #+#             */
/*   Updated: 2024/09/26 10:55:31 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

pid_t	exe_duplicate_of(t_cmd *cm)
{
	pid_t	pid;

	pid = fork();
 	if (pid == -1)
		applyerror();
	if (pid == 0)
	{
		dup2(ms()->in_fd,STDIN_FILENO);
		dup2(ms()->out_fd,STDOUT_FILENO);

		if(ms()->out_fd != 1)
			close(ms()->out_fd);
		real_execute(cm);
	}
	return(pid);
}

pid_t exe_pipe(t_cmd *cm)
{
	pid_t	pid;
	pid_t	pid2;
	int		i;
	pid = fork();
 	if (pid == -1)
		applyerror();
	if (pid == 0)
	{
		i = 0;
		while(i < cm->ofnum)
		{
			cm->outfile = cm->of[i++];
			set_fd(cm);
			pid2 = exe_duplicate_of(cm);
		}
		waitpid(pid2,NULL,0);
		dup2(ms()->in_fd,STDIN_FILENO);
		dup2(ms()->fd[1],STDOUT_FILENO);
		close(ms()->fd[0]);
		close(ms()->fd[1]);
		real_execute(cm);
	}

	return(pid);
}

pid_t exe_pipe3(t_cmd *cm)
{
	pid_t	pid;
	pid_t	pid2;

	int		i;
	pid = fork();
 	if (pid == -1)
		applyerror();
	if (pid == 0)
	{
		i = 0;
		while(i < cm->ofnum)
		{
			cm->outfile = cm->of[i++];
			set_fd(cm);
			close(ms()->fd[1]);
			pid2 = exe_duplicate_of(cm);
		}
		waitpid(pid2,NULL,0);
		if (cm->ofnum == 0)
		{
			dup2(ms()->fd[0],STDIN_FILENO);
			dup2(ms()->out_fd,STDOUT_FILENO);
			close(ms()->fd[1]);
			close(ms()->fd[0]);
			real_execute(cm);
		}
	}
	return(pid);
}
