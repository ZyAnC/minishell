/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:49:16 by yzheng            #+#    #+#             */
/*   Updated: 2024/09/25 11:22:17 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"
void	exe_pipe(t_cmd *cm)
{
	pid_t pid;

	if(pipe(ms()->fd) == -1)
		applyerror();
	pid = fork();
	if (pid == -1)
		applyerror();
	if(pid == 0)
	{
		dup2(ms()->in_fd, STDIN_FILENO);
		if(ms()->in_fd != 0)
			close(ms()->in_fd);
		dup2(ms()->fd[1], STDOUT_FILENO);
		close(ms()->fd[0]);
		close(ms()->fd[1]);
		real_execute(cm);
		ex_error();
	}
		waitpid(pid, NULL, 0);
	close(ms()->fd[1]);
	if (ms()->in_fd  !=  STDIN_FILENO)
		close(ms()->in_fd);
	cm->next->prepipe = 1;

	//restart(0);
}

void	exe_pipe2(t_cmd *cm)
{
	int		fd[2];
	fd[0] = ms()->fd[0];
	fd[1] = ms()->fd[1];

	if(pipe(ms()->fd) == -1)
		applyerror();
	pid_t pid;
	pid = fork();
	if (pid == -1)
		applyerror();
	if(pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(ms()->fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(ms()->fd[0]);
		close(ms()->fd[1]);
		real_execute(cm);
		ex_error();
	}
	waitpid(pid, NULL, 0);
	close(fd[0]);
	close(ms()->fd[1]);
	cm->next->prepipe = 1;

	//restart(0);
}

void	exe_pipe3(t_cmd *cm)
{
	pid_t pid;
	pid = fork();
	if (pid == -1)
		applyerror();
	if(pid == 0)
	{

		dup2(ms()->out_fd, STDOUT_FILENO);
		if(ms()->out_fd != 1)
			close(ms()->out_fd);
		dup2(ms()->fd[0], STDIN_FILENO);
		close(ms()->fd[0]);
		close(ms()->fd[1]);
		real_execute(cm);
		ex_error();
	}
	waitpid(pid, NULL, 0);
	close(ms()->fd[0]);
	if (ms()->out_fd  !=  STDOUT_FILENO)
		close(ms()->out_fd);

	//restart(0);
}


void	exe_simple(t_cmd *cm)
{
	pid_t pid;
	pid = fork();
	if (pid == -1)
		applyerror();
	if(pid == 0)
	{

		dup2(ms()->in_fd, STDOUT_FILENO);
		if(ms()->in_fd != 0)
		{
			ft_printf("close\n\n\n\n\n\n");
				close(ms()->in_fd);
		}
		dup2(ms()->out_fd, STDOUT_FILENO);
		if(ms()->out_fd != 1)
		{

			close(ms()->out_fd);
			ft_printf("close out\n\n\n\n\n\n");
		}
		real_execute(cm);
		ex_error();
	}
	 waitpid(pid, NULL, 0);
	 if(ms()->in_fd != 0)
		close(ms()->in_fd);
	if(ms()->out_fd != 1)
		close(ms()->out_fd);
	 //restart(0);
}
